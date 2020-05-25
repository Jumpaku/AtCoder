#include "../template.hpp"

/**
 * BIG＿NUMBERS
 * Requires Boost!
 */
#ifdef JUMPAKU_NO_BOOST
namespace mp = std;
using big_float = lf;
using big_integer = ll;
#else
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
using big_float = mp::cpp_dec_float_100;
using big_integer = mp::cpp_int;
#endif
/* end of BIG＿NUMBERS */
