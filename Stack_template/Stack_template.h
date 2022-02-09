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
		Node(T data, Node<T>* next) : m_data(data), m_next(next) {
			//default
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

		//adding rule of five
		Stack(Stack<T>& src) {
			*this = src;
		}
		Stack<T>& operator=(Stack<T>& src) {
			if (this != &src) {
				~*this;
				m_top = src.m_top;
				m_depth = src.m_depth;
				src.m_top = nullptr;
				src.m_depth = 0;
			}
			return *this;
		}
		Stack(const Stack<T>&& src) {
			*this = std::move(src);
		}
		Stack<T>& operator=(Stack<T>&& src) {
			if (this != &src) {
				~*this;
				Stack<T> temp;
				while (src.m_depth > 0) {
					temp.push(src.pop());
				}
				while (temp.m_depth > 0) {
					push(temp.pop());
				}
				src.m_top = nullptr;
			}
			return *this;
		}
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
			T data{};
			if (!isEmpty()) {
				data = m_top->m_data;
				Node<T>* del = m_top;
				m_top = m_top->m_next;
				delete del;
				m_depth--;
			}
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
		void operator ~() {
			while (m_top) {
				pop();
			}
		}

	};


}

#endif // !SDDS_STACK_TEMPLATE
