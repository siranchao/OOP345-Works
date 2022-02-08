#ifndef SDDS_STACK_TEMPLATE
#define SDDS_STACK_TEMPLATE
namespace sdds {

	template<typename T>
	class Stack;
	
	template<typename T>
	class Node {
		T m_data;
		Node<T>* m_next{};
		friend class Stack<T>;
		Node(T data, Node<T>* next) {
			m_data = data;
			m_next = next;
		}
	};

	template<typename T>
	class Stack {
		Node<T>* m_top{};
		size_t m_depth{};
	public:
		Stack() {
			//default empty
		};
		virtual ~Stack() {
			Node<T>* todel = m_top;
			while (m_top != nullptr) {
				m_top = m_top->m_next;
				delete todel;
				todel = m_top;
			}
		}

		Stack<T>& push(T data) {
			m_top = new Node<T>(data, m_top);
			m_depth++;
			return *this;
		}

		T pop() {
			T data = m_top->m_data;
			Node<T>* del = m_top;
			m_top = m_top->m_next;
			delete del;
			m_depth--;
			return data;
		}

		bool isEmpty()const {
			return m_top == nullptr;
		}
		operator bool()const {
			return m_top != nullptr;
		}
		size_t depth()const {
			return m_depth;
		}

	};


}

#endif // !SDDS_STACK_TEMPLATE
