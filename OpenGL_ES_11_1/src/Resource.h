#pragma once

class Resource {
public:
	Resource(const char* pPath);

	const char* getPath();

	status open();
	void close();
	status read(void* pBuffer, size_t pCount);

	off_t getLength();
	const void* bufferize();

private:
	const char* mPath;
};