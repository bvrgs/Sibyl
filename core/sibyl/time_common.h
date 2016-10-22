/* ========================================================================== */
/*  Copyright (C) 2016 Hosang Yoon (hosangy@gmail.com) - All Rights Reserved  */
/*  Unauthorized copying of this file, via any medium is strictly prohibited  */
/*                        Proprietary and confidential                        */
/* ========================================================================== */

#ifndef SIBYL_TIME_COMMON_H_
#define SIBYL_TIME_COMMON_H_

namespace sibyl
{

namespace kTimeRates
{
    constexpr int secPerTick = 10;
    constexpr int reqPerSec  = 5;                      // as required by Kiwoom  
    constexpr int reqPerTick = reqPerSec * secPerTick; // maximum number of reqs possible in a tick
}

namespace kTimeBounds // [seconds]
{
    constexpr int null =              -9 * 3600; // defines conversion to 00:00:00-based time
    constexpr int ref  =                  -3600; // 08:00:00 last ref price reference
    constexpr int init = kTimeRates::secPerTick; // 09:00:10 initiate rnn
    constexpr int stop =                  21000; // 14:50:00 stop rnn
    constexpr int end  =                  24000; // 15:40:00 end everything
}

}

#endif /* SIBYL_TIME_COMMON_H_ */