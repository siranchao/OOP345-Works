#ifndef SDDS_FILE_H__
#define SDDS_FILE_H__
#include "Resource.h"
namespace sdds {

	class File: public Resource {
		std::string m_contents{};

	public:
		File();
		File(std::string fileName, std::string contents = "");
		void update_parent_path(const std::string& path);
		
		NodeType type() const;
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;

		~File();
	};












}


#endif // !SDDS_FILE_H__

