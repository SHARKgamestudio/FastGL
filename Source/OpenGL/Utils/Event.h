#pragma once

#include <vector>
#include <functional>

namespace OpenGL {
	/// <summary>
	/// Generic event class used throughout the library for callbacks.
	/// <para>WARNING: This is very performance-hungry and should not be called in performance-critical hot loops.</para>
	/// <para>If you wish to, with a bit of effort, it should be trivial to swap out this implementation for something simpler and more performant.</para>
	/// </summary>
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

		/// <summary>
		/// Executes the callbacks registered on every listener.
		/// </summary>
		/// <param name="args">Generic variadic arguments passed to callbacks.</param>
		void invoke(Args... args);

		/// <summary>
		/// Registers a callback function or lambda to listen to this event.
		/// </summary>
		/// <param name="func"> A function pointer to the callback. </param>
		/// <returns> A generated listener object. This object must be stored if you want to unregister the callback later. </returns>
		ListenerBase* addListener(funcptr func);

		/// <summary>
		/// Registers a callback method to listen to this event.
		/// </summary>
		/// <param name="method"> A method pointer to the callback. </param>
		/// <param name="inst"> The instance on which the callback method will be invoked. </param>
		/// <returns> A generated listener object. This object must be stored if you want to unregister the callback later. </returns>
		template <class C> ListenerBase* addListener(methodptr<C> method, C* inst);

		/// <summary>
		/// Registers a const callback method to listen to this event.
		/// </summary>
		/// <param name="method"> A method pointer to the const callback. </param>
		/// <param name="inst"> The instance on which the const callback method will be invoked. </param>
		/// <returns> A generated listener object. This object must be stored if you want to unregister the callback later. </returns>
		template <class C> ListenerBase* addListener(cmethodptr<C> method, C const* inst);

		/// <summary>
		/// Unregister a callback by its generated Listener object.
		/// </summary>
		/// <param name="listener"> The generated Listener object associated with your callback. You can obtain this object by storing the return value of the "addListener" method. </param>
		void removeListener(ListenerBase* listener);

		/// <summary>
		/// Removes all associated callbacks listening to this event.
		/// <para> This method is called by the destructor when this object gets deleted. </para>
		/// </summary>
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