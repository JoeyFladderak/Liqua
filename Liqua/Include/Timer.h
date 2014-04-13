#ifndef _TIMER_H_
#define _TIMER_H_

namespace Liqua
{
	class LIQUAEXPORT Timer
	{
	public:

		Timer();
		virtual ~Timer();

		void Start();
		void End();

		const float GetTime() const;

	protected:

		const double LargeIntToSeconds(LARGE_INTEGER& a_LargeInt) const;

		LARGE_INTEGER m_Start;
		LARGE_INTEGER m_End;
		LARGE_INTEGER m_Frequency;

	};
};

#endif