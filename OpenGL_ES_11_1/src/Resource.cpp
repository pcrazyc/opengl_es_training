#include "resource.h"


Resource::Resource(const char* pPath):
mPath(pPath)
{
}

status Resource::open() {
	//todo
	return STATUS_OK;
}

void Resource::close() {
	//if (mAsset != NULL) {
	//	AAsset_close(mAsset);
	//	mAsset = NULL;
	//}
	//todo
}

status Resource::read(void* pBuffer, size_t pCount) {
	//int32_t lReadCount = AAsset_read(mAsset, pBuffer, pCount);
	//return (lReadCount == pCount) ? STATUS_OK : STATUS_KO;
	//todo

}

const char* Resource::getPath() {
	return mPath;
}

off_t Resource::getLength() {
	/*return AAsset_getLength(mAsset);*/
}

const void* Resource::bufferize() {
	/*return AAsset_getBuffer(mAsset);*/
}