#ifndef _COMPLETE_USER_EXPERIENCE_DATA_DEF_H_
#define _COMPLETE_USER_EXPERIENCE_DATA_DEF_H_

#include <boost/unordered_map.hpp>

namespace dy
{
namespace complete_user_exp
{

typedef boost::unordered_map<unsigned int, unsigned long> UidExperienceMap;

typedef boost::unordered_map<unsigned int, int> UidSilverMap;

typedef boost::unordered_map<unsigned int, int> UidGoldMap;

} // !namespace complete_user_exp
} // !namespace dy

#endif // _COMPLETE_USER_EXPERIENCE_DATA_DEF_H_

