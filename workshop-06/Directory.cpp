#include "Directory.h"

namespace sdds {

	Directory::Directory() {
		//default
	}
	Directory::Directory(std::string dirName) {
		m_name = dirName;
	}

	void Directory::update_parent_path(const std::string& path) {
		m_parent_path = path;
		if (!m_contents.empty()) {
			for (auto ele : m_contents) {
				ele->update_parent_path(this->path());
			}
		}
	}

	NodeType Directory::type() const {
		return NodeType::DIR; 
	}
	std::string Directory::path() const {
		return m_parent_path + m_name;
	}
	std::string Directory::name() const {
		return m_name;
	}
	int Directory::count() const {
		return m_contents.size();
	}
	size_t Directory::size() const {
		size_t val = 0u;
		if (!m_contents.empty()) {
			for (auto& ele : m_contents) {
				val += ele->size();
			}
		}
		return val;
	}

	Directory& Directory::operator+=(Resource* newRes) {
		if (newRes) {
			bool found = false;
			if (!m_contents.empty()) {
				for (size_t i = 0; i < m_contents.size() && !found; i++) {
					if (m_contents[i]->name() == newRes->name()) {
						found = true;
					}
				}
				//if (find(newRes->name())) {
				//	found = true;
				//}
			}
			if (found) {
				throw std::string("There is already an resource with the same name");
			}
			else {
				newRes->update_parent_path(this->path());
				m_contents.push_back(newRes);
			}
		}
		return *this;
	}

	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
		bool found = false;
		Resource* val{};
		if (!m_contents.empty()) {
			for (size_t i = 0; i < m_contents.size() && !found; i++) {
				if (m_contents[i]->name() == name) {
					found = true;
					val = m_contents[i];
				}
			}

			if (flags.size() > 0 && flags.back() == OpFlags::RECURSIVE) {
				for (auto& ele : m_contents) {
					if (ele->type() == NodeType::DIR) {
						val = dynamic_cast<Directory*>(ele)->find(name, flags);
					}
				}
			}
		}
		return val;
	}

	Directory::~Directory() {
		if (!m_contents.empty()) {
			for (auto& ele : m_contents) {
				delete ele;
				ele = nullptr;
			}
		}
	}

	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
		auto ptr = find(name);
		if (ptr) {
			for (auto& ele : m_contents) {
				if (ele->name() == name) {
					if (ele->type() == NodeType::DIR) {
						if (flags.size() > 0 && flags.back() == OpFlags::RECURSIVE) {
							delete ele;
						}
						else {
							throw std::invalid_argument("NAME is a directory. Pass the recursive flag to delete directories.");
						}
					}
					else {
						delete ele;
					}
					m_contents.erase(findPos(ptr));
				}
			}
		}
		else {
			throw std::string("NAME does not exist in DIRECTORY_NAME");
		}
	}

	void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
		os << "Total size: " << size() << " bytes" << std::endl;
		char type{};
		for (auto& ele : m_contents) {
			type = (ele->type() == NodeType::DIR) ? 'D' : 'F';
			os << type << " | ";
			os.width(15);
			os.setf(std::ios::left);
			os << ele->name() << " |";
			os.unsetf(std::ios::left);
			if (flags.size() > 0 && flags.back() == FormatFlags::LONG) {
				os << " ";
				if (type == 'D') {
					os.width(2);
					os << ele->count();
				}
				else {
					os << "  ";
				}
				os << " | ";
				os.width(4);
				os << ele->size() << " bytes | ";
			}
			os << std::endl;
		}
	}

	auto Directory::findPos(Resource* ptr)->std::vector<Resource*>::iterator const {
		auto pos = m_contents.begin();
		while (*pos != ptr && pos < m_contents.end()) {
			pos++;
		}
		return pos;
	}
}