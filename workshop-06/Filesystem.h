#ifndef SDDS_FILESYSTEM_H__
#define SDDS_FILESYSTEM_H__
#include <string>
namespace sdds {
	class Directory;
	class Resource;
	class Filesystem {
		Directory* m_root{};
		Directory* m_current{};

	public:
		Filesystem();
		Filesystem(std::string fileName, std::string rootName = "");
		Filesystem(const Filesystem& src) = delete;
		Filesystem& operator=(const Filesystem& src) = delete;
		Filesystem(Filesystem&& src);
		Filesystem& operator=(Filesystem&& src);
		~Filesystem();
		Filesystem& operator+=(Resource* newRes);
		Directory* change_directory(const std::string& nextDir = "");
		Directory* get_current_directory() const;

	private:
		std::string& trim(std::string& str)const;
		void createRes(std::string& path, std::string content = "");

	};


}

#endif // !SDDS_FILESYSTEM_H__

