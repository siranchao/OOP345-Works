#ifndef SDDS_STACK_MODULE
#define SDDS_STACK_MODULE
namespace sdds {

	class Stack;

	class Node {
		int m_data;
		Node* m_next{};
		friend class Stack;
		Node(int data, Node* next) {
			m_data = data;
			m_next = next;
		}
	};


	class Stack {
		Node* m_top{};
	public:
		Stack() {
			//default empty
		};
		virtual ~Stack() {
			while (*this) {
				pop();
			}
		}

		Stack& push(int data) {
			Node* temp = new Node(data, m_top);
			m_top = temp;
			return *this;
		}

		int pop() {
			int data = m_top->m_data;
			Node* del = m_top;
			m_top = m_top->m_next;
			delete del;
			return data;
		}

		bool isEmpty()const {
			return m_top == nullptr;
		}

		operator bool()const {
			return m_top != nullptr;
		}

		void operator ~() {
			while (m_top) {
				pop();
			}
		}



	};


}

#endif // !SDDS_STACK_MODULE
