#ifndef _CC_DATAMANAGER_H_
#define _CC_DATAMANAGER_H_

#include "cocoa/CCObject.h"

namespace cocos2d
{
	class ZipStream;
	class CCDataStream : public CCObject
	{
		friend class CCDataManager;
	public:
		virtual ~CCDataStream();

		virtual bool eof();
		virtual size_t size();
		virtual void readline(std::string& _source, char _delim = '\n');
		virtual size_t read(void* _buf, size_t _count);

	private:
		ZipStream* mStream;
	};

	class CCDataManager : public CCObject
	{
	public:
		CCDataManager();
		~CCDataManager();

		void init(const std::string& _path);

		virtual CCDataStream* getData(const std::string& _name);
		virtual void freeData(CCDataStream* _data);
		virtual bool isDataExist(const std::string& _name);
	private:
		CCDictionary* mStreamPool;
		std::string mPackage;
	};

}

#endif