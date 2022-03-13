#include <fstream>
#include <exception>
#include "Filesystem.h"
#include "Directory.h"
#include "File.h"

namespace sdds {

   Filesystem::Filesystem() {
      //default
   }
   Filesystem::Filesystem(std::string fileName, std::string rootName) {
      //open file
      std::fstream fs(fileName);
      if (!fs) {
         throw std::invalid_argument("File cannot be opened.");
      }
      else {
         m_root = new Directory(rootName);
         m_current = m_root;

         //read file
         std::string str, path, content;
         while (!fs.eof()) {
            getline(fs, str);
            if (str.back() != '/') {
               //it's a file
               path = str.substr(0, str.find('|'));
               trim(path);
               content = str.erase(0, str.find('|') + 1);
               trim(content);
               createRes(path, content);
            }
            else {
               //it's a directory
               path = trim(str);
               createRes(path);
            }
         }
         fs.close();
      }
   }


   Filesystem::Filesystem(Filesystem&& src) {
      *this = std::move(src);
   }
   Filesystem& Filesystem::operator=(Filesystem&& src) {
      if (this != &src) {
         delete m_root;
         m_root = src.m_root;
         m_current = src.m_current;
         src.m_root = nullptr;
         src.m_current = nullptr;
      }
      return *this;
   }
   Filesystem::~Filesystem() {
      delete m_root;
   }

   Filesystem& Filesystem::operator+=(Resource* newRes) {
      if (newRes) {
         bool found = false;
         if (m_current->count() > 0) {
            if (m_current->find(newRes->name())) {
               found = true;
            }
         }
         if (found) {
            throw std::string("There is already an resource with the same name");
         }
         else {
            newRes->update_parent_path(m_current->path());
            *m_current += newRes;
         }
      }
      return *this;
   }

   Directory* Filesystem::change_directory(const std::string& nextDir) {
      if (nextDir == "") {
         m_current = m_root;
      }
      else {
         if (m_current->find(nextDir)) {
            m_current = dynamic_cast<Directory*>(m_current->find(nextDir));
         }
         else {
            throw std::invalid_argument("Cannot change directory!DIR_NAME not found!");
         }
      }
      return m_current;
   }

   Directory* Filesystem::get_current_directory() const {
      return m_current;
   }

   
   std::string& Filesystem::trim(std::string& str)const {
      while (str[0] == ' ') {
         str.erase(0, str.find_first_not_of(' '));
      }
      while (str[str.size() - 1] == ' ') {
         str.erase(str.find_last_not_of(' ') + 1);
      }
      return str;
   }

   void Filesystem::createRes(std::string& path, std::string content) {
      if (path != "") {
         std::string component{};
         Resource* newRes{};
         if (path.find('/') != std::string::npos) {
            component = path.substr(0, path.find('/') + 1);
            path.erase(0, path.find('/') + 1);
            //create dir //check exist
            if (!m_current->find(component)) {
               newRes = new Directory(component);
               newRes->update_parent_path(m_current->path());
               *m_current += newRes;
            }
            change_directory(component);
         }
         else {
            component = path;
            path.erase(0, path.length());
            //create file //check exist
            if (!m_current->find(component)) {
               newRes = new Directory(component);
               newRes->update_parent_path(m_current->path());
               *m_current += newRes;
            }
         }
         createRes(path, content);
      }
      else {
         change_directory();
      }
   }


}