// time.hpp

#pragma once

namespace papaya {
   using int64 = long long;

   class Time {
   public:
      static Time now();

   public:
      Time();
      Time(const int64 ticks);
      Time(const Time &rhs);

      Time &operator+=(const Time &rhs);
      Time &operator-=(const Time &rhs);
      Time operator+(const Time &rhs) const;
      Time operator-(const Time &rhs) const;
      bool operator==(const Time &rhs) const;
      bool operator!=(const Time &rhs) const;
      bool operator< (const Time &rhs) const;
      bool operator<=(const Time &rhs) const;
      bool operator> (const Time &rhs) const;
      bool operator>=(const Time &rhs) const;

      float as_seconds() const;
      int   as_milliseconds() const;
      int64 as_microseconds() const;

   private:
      int64 microseconds_;
   };

   namespace time {
      Time seconds(const double duration);
      Time milliseconds(const int64 duration);
      Time microseconds(const int64 duration);
   } // !time
} // !papaya
