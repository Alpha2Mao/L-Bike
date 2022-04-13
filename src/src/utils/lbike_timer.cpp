//
// Created by 杜晓磊 on 2022/4/12.
//
#include "utils/lbike_timer.h"
#include <atomic>
#include <chrono>
#include <thread>
#include <assert.h>

namespace lbike {
    class TimerImpl {
    public:
        TimerImpl() : m_stop(false), m_running(false), m_last_error(0) {}

        TimerImpl(const int timeout_, TimerCallbackT callback_, const int delay_) :
                m_stop(false), m_running(false) {
            Start(timeout_, callback_, delay_);
        }

        virtual ~TimerImpl() {
            Stop();
        }

        bool Start(const int timeout_, TimerCallbackT callback_, const int delay_) {
            assert(m_running == false);
            if (m_running) return false;
            if (timeout_ < 0) return false;
            m_stop = false;
            m_thread = std::thread(&TimerImpl::Thread, this, callback_, timeout_, delay_);
            m_running = true;
            return true;
        }

        bool Stop() {
            if (!m_running)
                return false;
            m_stop = true;
            m_thread.join();
            m_running = false;
            return true;
        }


    private:
        std::atomic<bool>                   m_stop;
        std::atomic<bool>                   m_running;
        std::thread                         m_thread;
        std::chrono::nanoseconds            m_last_error;


    private:
        void Thread(TimerCallbackT callback_, int timeout, int delay_) {
            assert(callback_ != nullptr);
            if (callback_ == nullptr)
                return;
            if (delay_ > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_));
            }

            std::chrono::nanoseconds loop_duration((long long) timeout * 1000LL * 1000LL);
            m_last_error = std::chrono::nanoseconds(0);

            while (!m_stop) {
                auto start = std::chrono::system_clock::now();
                (callback_());
                auto end = std::chrono::system_clock::now();
                if (end < start) {
                    std::this_thread::sleep_for(loop_duration);
                } else {
                    auto loop_duration_corr = loop_duration - m_last_error;
                    auto sleep_remaining = loop_duration_corr - (end -start);
                    std::this_thread::sleep_for(sleep_remaining);
                    m_last_error = (std::chrono::system_clock::now() - start) - loop_duration_corr;
                }
            }
            m_stop = false;
        }
    };

    bool Timer::Stop() {
        return m_timer->Stop();
    }

    Timer::Timer() : m_timer(nullptr){
        m_timer = new TimerImpl();
    }

    Timer::Timer(int timeout_, TimerCallbackT callback_, int delay_) {
        m_timer = new TimerImpl();
        m_timer->Start(timeout_, callback_, delay_);
    }

    Timer::~Timer() {
        Stop();
        delete m_timer;
    }

    bool Timer::Start(int timeout_, TimerCallbackT callback_, int delay_) {
        return (m_timer->Start(timeout_, callback_, delay_));
    }
}
