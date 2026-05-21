#pragma once

#include <vector>
#include <functional>

namespace OpenGL {
	template <typename ...Args>
	struct Event {
		struct ListenerBase;

		using funcptr = std::function<void(Args...)>; // Uses std::functional for type erasure / lambda capture
		template <class C> using methodptr = void(C::*)(Args...);
		template <class C> using cmethodptr = void(C::*)(Args...) const;

		Event() = default;
		~Event() { clearListeners(); }

		Event(Event const&) = default;
		Event(Event&&) = default;
		Event& operator=(Event const&) = default;
		Event& operator=(Event&&) = default;

		void invoke(Args... args);

		ListenerBase* addListener(funcptr func);
		template <class C> ListenerBase* addListener(methodptr<C> method, C* inst);
		template <class C> ListenerBase* addListener(cmethodptr<C> method, C const* inst);
		void removeListener(ListenerBase* listener);
		void clearListeners();

	private:
		struct FunctionListener;
		template <class C> struct MethodListener;
		template <class C> struct MethodListenerConst;

		std::vector<ListenerBase*> m_listeners;
	};


	template <typename ...Args>
	struct Event<Args...>::ListenerBase {
		ListenerBase() = default;
		virtual ~ListenerBase() = default;

		ListenerBase(ListenerBase const&) = delete;
		ListenerBase(ListenerBase&&) = delete;
		ListenerBase& operator=(ListenerBase const&) = delete;
		ListenerBase& operator=(ListenerBase&&) = delete;

		virtual void invoke(Args... args) = 0;
	};


	template <typename ...Args>
	struct Event<Args...>::FunctionListener final : ListenerBase {
		explicit FunctionListener(funcptr const func) : m_funcptr(func) {}
		~FunctionListener() override = default;

		FunctionListener(FunctionListener const&) = delete;
		FunctionListener(FunctionListener&&) = delete;
		FunctionListener& operator=(FunctionListener const&) = delete;
		FunctionListener& operator=(FunctionListener&&) = delete;

		void invoke(Args... args) override { m_funcptr(args...); }

	private:
		funcptr m_funcptr = nullptr;
	};


	template <typename ...Args>
	template <class C>
	struct Event<Args...>::MethodListener final : ListenerBase {
		explicit MethodListener(methodptr<C> const method, C* const inst) : m_methodptr(method), m_inst(inst) {}
		~MethodListener() override = default;

		MethodListener(MethodListener const&) = delete;
		MethodListener(MethodListener&&) = delete;
		MethodListener& operator=(MethodListener const&) = delete;
		MethodListener& operator=(MethodListener&&) = delete;

		void invoke(Args... args) override { (m_inst->*m_methodptr)(args...); }

	private:
		methodptr<C> m_methodptr = nullptr;
		C* m_inst = nullptr;
	};


	template <typename ...Args>
	template <class C>
	struct Event<Args...>::MethodListenerConst final : ListenerBase {
		explicit MethodListenerConst(cmethodptr<C> const method, C const* const inst) : m_methodptr(method), m_inst(inst) {}
		~MethodListenerConst() override = default;

		MethodListenerConst(MethodListenerConst const&) = delete;
		MethodListenerConst(MethodListenerConst&&) = delete;
		MethodListenerConst& operator=(MethodListenerConst const&) = delete;
		MethodListenerConst& operator=(MethodListenerConst&&) = delete;

		void invoke(Args... args) override { (m_inst->*m_methodptr)(args...); }

	private:
		cmethodptr<C> m_methodptr = nullptr;
		C const* m_inst = nullptr;
	};


	template <typename... Args>
	void Event<Args...>::invoke(Args... args) { for (ListenerBase* const listener : m_listeners) listener->invoke(args...); }


	template <typename ...Args>
	typename Event<Args...>::ListenerBase* Event<Args...>::addListener(funcptr const pListener) {
		ListenerBase* const result = new FunctionListener(pListener);
		m_listeners.push_back(result);
		return result;
	}

	template <typename ...Args> template <class C>
	typename Event<Args...>::ListenerBase* Event<Args...>::addListener(methodptr<C> const pListener, C* const pClass) {
		ListenerBase* const result = new MethodListener<C>(pListener, pClass);
		m_listeners.push_back(result);
		return result;
	}

	template <typename ...Args> template <class C>
	typename Event<Args...>::ListenerBase* Event<Args...>::addListener(cmethodptr<C> const pListener, C const* const pClass) {
		ListenerBase* const result = new MethodListenerConst<C>(pListener, pClass);
		m_listeners.push_back(result);
		return result;
	}

	template <typename... Args>
	void Event<Args...>::removeListener(ListenerBase* const listener) {
		for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
			if (*it != listener) continue;
			m_listeners.erase(it);
			delete listener;
			return;
		}
	}

	template <typename... Args>
	void Event<Args...>::clearListeners() {
		for (ListenerBase const* const listener : m_listeners) delete listener;
		m_listeners.clear();
	}
}