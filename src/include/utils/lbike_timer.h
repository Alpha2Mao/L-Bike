//
// Created by 杜晓磊 on 2022/4/12.
//

#ifndef L_BIKE_LBIKE_TIMER_H
#define L_BIKE_LBIKE_TIMER_H

#pragma once
#include <functional>

namespace lbike
{
    class TimerImpl;
    typedef std::function<void(void)> TimerCallbackT;

    class Timer
    {
    public:
        Timer();

        /**
         * @brief Constructor.
         *
         * @param timeout_ Timer callback loop time in ms
         * @param callback_ The callback function.
         * @param delay_ Timer callback delay for first call in ms
         */
        Timer(int timeout_, TimerCallbackT callback_, int delay_ = 0);
        virtual ~Timer();

        /**
         * @brief Start the timer.
         *
         * @param timeout_ Timer callback loop time in ms.
         * @param callback_ The callback function.
         * @param delay_ Timer callback delay for first call in ms.
         *
         * @return True if timer can be started.
         */
        bool Start(int timeout_, TimerCallbackT callback_, int delay_ = 0);

        /**
         * @brief Stop the timer.
         *
         * @return True if the time can be stopped.
         */
        bool Stop();


    protected:
        // class members
        TimerImpl* m_timer;

    private:
        Timer(const Timer&);
        Timer& operator=(const Timer&);
    };
}

#endif //L_BIKE_LBIKE_TIMER_H
