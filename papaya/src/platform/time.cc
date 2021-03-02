// time.cc

#include "platform/time.hpp"

#include <SDL.h>

namespace papaya {
   // static 
   Time Time::now()
   {
      static Uint64 start = 0;
      static Uint64 factor = 0;
      if (factor == 0) {
         start = SDL_GetPerformanceCounter();
         const Uint64 frequency = SDL_GetPerformanceFrequency();
         factor = frequency / 1000000;
      }

      const Uint64 current = SDL_GetPerformanceCounter();
      const Sint64 microseconds = static_cast<Sint64>(current - start) / static_cast<Sint64>(factor);
      return { microseconds };
   }

   Time::Time()
      : microseconds_(0)
   {
   }

   Time::Time(const int64 ticks)
      : microseconds_(ticks)
   {
   }

   Time::Time(const Time &rhs)
      : microseconds_(rhs.microseconds_)
   {
   }

   Time &Time::operator+=(const Time &rhs)
   {
      microseconds_ += rhs.microseconds_;
      return *this;
   }

   Time &Time::operator-=(const Time &rhs)
   {
      microseconds_ -= rhs.microseconds_;
      return *this;
   }

   Time Time::operator+(const Time &rhs) const
   {
      return { microseconds_ + rhs.microseconds_ };
   }

   Time Time::operator-(const Time &rhs) const
   {
      return { microseconds_ - rhs.microseconds_ };
   }

   bool Time::operator==(const Time &rhs) const
   {
      return microseconds_ == rhs.microseconds_;
   }

   bool Time::operator!=(const Time &rhs) const
   {
      return microseconds_ != rhs.microseconds_;
   }

   bool Time::operator< (const Time &rhs) const
   {
      return microseconds_ < rhs.microseconds_;
   }

   bool Time::operator<=(const Time &rhs) const
   {
      return microseconds_ <= rhs.microseconds_;
   }

   bool Time::operator> (const Time &rhs) const
   {
      return microseconds_ > rhs.microseconds_;
   }

   bool Time::operator>=(const Time &rhs) const
   {
      return microseconds_ >= rhs.microseconds_;
   }

   float Time::as_seconds() const
   {
      return static_cast<float>(microseconds_ * 0.000001);
   }

   int Time::as_milliseconds() const
   {
      return static_cast<int>(microseconds_ / 1000);
   }

   int64 Time::as_microseconds() const
   {
      return microseconds_;
   }


   namespace time {
      Time seconds(const double duration)
      {
         return { static_cast<int64>(duration * 1000000.0) };
      }

      Time milliseconds(const int64 duration)
      {
         return { duration * 1000 };
      }

      Time microseconds(const int64 duration)
      {
         return { duration };
      }
   } // !time
} // !papaya
