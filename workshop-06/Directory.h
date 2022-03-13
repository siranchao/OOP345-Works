#ifndef SDDS_DIRECTORY_H__
#define SDDS_DIRECTORY_H__
#include <vector>
#include "Resource.h"
namespace sdds {

	class Directory: public Resource {
		std::vector<Resource*> m_contents{};

	public:
		Directory();
		Directory(std::string dirName);
		void update_parent_path(const std::string& path);
		
		NodeType type() const;
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;

		Directory& operator+=(Resource* newRes);
		Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {});
		Directory(const Directory&) = delete;
		Directory& operator=(const Directory&) = delete;
		Directory(Directory&&) = delete;
		Directory& operator=(Directory&&) = delete;
		~Directory();

		void remove(const std::string& name, const std::vector<OpFlags>& flags = {});
		void display(std::ostream& os = std::cout, const std::vector<FormatFlags>& flags = {}) const;

	private:
		auto findPos(Resource* ptr)->std::vector<Resource*>::iterator const;
	};








}
#endif // !SDDS_DIRECTORY_H__

