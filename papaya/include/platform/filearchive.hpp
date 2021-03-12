#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace papaya
{
	class FileStream;

	class FileArchive
	{
	public:
		FileArchive(FileStream &stream);

		bool open();
		void close();

		bool contains(const std::string &filename) const;
		bool extract(const std::string &filename,
						 std::vector<char> &uncompressed);

	private:
		FileStream &stream_;

		struct Entry
		{
			unsigned int data_offset_;
			unsigned int size_compressed_;
			unsigned int size_uncompressed_;
		};

		std::unordered_map<std::string, Entry> entries_;
	};
} // !papaya