#include "CCDataManager.h"

namespace cocos2d
{

	/////////////////////////////////////////////////////////
	class ZipStream
	{
	public:
		ZipStream(const std::string& path)
		{

		}
	private:

	};
	/////////////////////////////////////////////////////////
	CCDataStream::~CCDataStream()
	{

	}

	bool CCDataStream::eof()
	{
		return true;
	}

	size_t CCDataStream::size()
	{
		return 0;
	}

	void CCDataStream::readline( std::string& _source, char _delim /*= '\n'*/ )
	{

	}

	size_t CCDataStream::read( void* _buf, size_t _count )
	{
		return 0;
	}

/////////////////////////////////////////////////////////

	CCDataManager::CCDataManager()
	{

	}

	CCDataManager::~CCDataManager()
	{

	}

	void CCDataManager::init( const std::string& _path )
	{

	}

	CCDataStream* CCDataManager::getData( const std::string& _name )
	{
		return NULL;
	}

	void CCDataManager::freeData( CCDataStream* _data )
	{

	}

	bool CCDataManager::isDataExist( const std::string& _name )
	{
		return false;
	}

}