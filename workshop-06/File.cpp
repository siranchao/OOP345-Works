#include "File.h"
namespace sdds {
	File::File() {
		//default
	}
	File::File(std::string fileName, std::string contents) {
		m_name = fileName;
		m_contents = contents;
	}

	void File::update_parent_path(const std::string& path) {
		m_parent_path = path;
	}

	NodeType File::type() const {
		return NodeType::FILE; 
	}
	std::string File::path() const {
		return m_parent_path + m_name;
	}
	std::string File::name() const {
		return m_name;
	}
	int File::count() const {
		return -1;
	}
	size_t File::size() const {
		return m_contents.size();
	}

	File::~File() { 
		//default
	}

}