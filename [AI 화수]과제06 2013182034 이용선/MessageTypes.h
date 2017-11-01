#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
	Msg_HiHoneyImHome,
	Msg_StewReady,
	Msg_MomImHome,
	Msg_FrenchFriesReady
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_MomImHome:

	  return "MomImHome";

  case Msg_FrenchFriesReady:

	  return "FrenchFriesReady";

  default:

    return "Not recognized!";
  }
}

#endif