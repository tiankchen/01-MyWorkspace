

#include <iostream>
#include <vector>
#include <map>

#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>


class OnlineDetector
{
public:
	//时间段<开始时间，结束时间>对象类型
	typedef std::pair<time_t, time_t>		DurationType;

	//<开始时间-时间段>映射表
	typedef std::map<time_t, DurationType>		DurationMapType;
	typedef DurationMapType::iterator				IteratorType;
	typedef DurationMapType::const_iterator		ConstIteratorType;

	enum RecoveryState
	{
		RECOVERY_STATE_ONLINE,				//一直在线
		RECOVERY_STATE_UN_RECOVERY,	//未回复
		RECOVERY_STATE_RECOVERY,			//已恢复
		RECOVERY_STATE_UNKNOWN,			//未知
	};

public:
	OnlineDetector()
		: m_begin(0)
		, m_end(0)
		, m_durations()
	{}

	//在线期间的开始时间和结束时间
	OnlineDetector(time_t begin, time_t end)
		: m_begin(begin)
		, m_end(end)
		, m_durations()
	{}

	/**
	 * @brief 增加在线时间段
	 */
	void AddOnlineDuration(const DurationType& d)
	{
		if (m_durations.find(d.first) == m_durations.end())
		{
			m_durations.insert(std::make_pair(d.first, d));
		}
		else
		{
			time_t t = d.first;
			DurationType result = MergeDuration(m_durations[t], d);
			m_durations[t] = result;
		}
	}

	/**
	 * @判断在线时间段是否已经覆盖了整个区间
	 */
	bool IsOnline()
	{
		if (m_durations.empty())
			return false;

		for (IteratorType it = m_durations.begin(); it != m_durations.end(); ++it)
		{
			DurationType d = it->second;
			if (d.first <= m_begin && d.second >= m_end)
			{
				return true;
			}
		}
		
		return false;
	}

	/**
	 * @brief 获取当前时间段恢复状态
	 */
	int GetRecoveryState() const
	{
		bool onlineOnBegin = false;		//初始时间点在线
		bool onlineOnEnd = false;			//结束时间点在线
		bool hasBreak = false;				//在规定时间段中有间隔

		for (ConstIteratorType it = m_durations.begin(); it != m_durations.end(); ++it)
		{
			DurationType d = it->second;
			if (d.first <= m_begin && d.second >= m_end)
			{
				return RECOVERY_STATE_ONLINE;
			}
			else if (d.first <= m_begin && d.second >= m_begin)
			{
				onlineOnBegin = true;
			}
			else if (d.first <= m_end&& d.second >= m_end)
			{
				onlineOnEnd = true;
			}
			
			//判断下一个时间段与当前时间之间的空白，是否会造成离线
			ConstIteratorType next = it;
			++next;
			if (next != m_durations.end())
			{
				if(d.second>m_begin && next->first <m_end)
				{
					hasBreak = true;
				}
			}
		}

		if (onlineOnBegin)
		{
			if (onlineOnEnd&& hasBreak)
			{
				return RECOVERY_STATE_RECOVERY;
			}
			else
			{
				return RECOVERY_STATE_UN_RECOVERY;
			}
		}
		else 
		{
			return RECOVERY_STATE_UNKNOWN;
		}
	}

	/**
	 * @brief 对整个时间段集合进行整理合并
	 */
	void Merge()
	{
		IteratorType it = m_durations.begin();
		while (it != m_durations.end())
		{
			IteratorType next = it;
			++next;
			if (next == m_durations.end())
			{
				break;		//it所指为最后一个有效时间段
			}

			if (HasIntersection(it->second, next->second))
			{
				DurationType result = MergeDuration(it->second, next->second);
				it->second = result;
				m_durations.erase(next);
			}
			else
			{
				++it;
			}
		}
	}

private:
	/**
	 * @brief 判断两个时间段之间是否有交集
	 */
	bool HasIntersection(const DurationType& d1, const DurationType& d2) const
	{
		//判断两个区域在一维坐标轴上分布
		DurationType leftDuration, rightDuration;
		if (d1.first <= d2.first)
		{
			leftDuration = d1;
			rightDuration = d2;
		}
		else
		{
			leftDuration = d2;
			rightDuration = d1;
		}

		if (rightDuration.first >= leftDuration.first && rightDuration.first <= leftDuration.second)
		{
			return true;	//靠左边区域的第一个点落在靠右区域中，即相交
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief 合并两个时间段
	 */
	DurationType MergeDuration(const DurationType& d1, const DurationType& d2) const
	{
		time_t first = d1.first <= d2.first ? d1.first : d2.first;
		time_t second = d1.second >= d2.second ? d1.second : d2.second;
		return DurationType(first, second);
	}

private:
	time_t m_begin;
	time_t m_end;
	DurationMapType m_durations;	//区域段之间相互独立
};

/**
 * @brief 测试时间段是否相交
 */
void Test1()
{
	typedef OnlineDetector::DurationType			DurationType;

	//OnlineDetector onlineDetector(1, 10);
	//assert(onlineDetector.HasIntersection(DurationType(0, 1), DurationType(2, 3)) == false);
	//assert(onlineDetector.HasIntersection(DurationType(0, 2), DurationType(2, 3)) == true);
	//assert(onlineDetector.HasIntersection(DurationType(0, 3), DurationType(2, 3)) == true);
	//assert(onlineDetector.HasIntersection(DurationType(4, 5), DurationType(2, 3)) == false);

	//assert(onlineDetector.MergeDuration(DurationType(0, 1), DurationType(2, 3)) == DurationType(0, 3));
	//assert(onlineDetector.MergeDuration(DurationType(0, 1), DurationType(0, 3)) == DurationType(0, 3));
	//assert(onlineDetector.MergeDuration(DurationType(0, 1), DurationType(1, 3)) == DurationType(0, 3));
	//assert(onlineDetector.MergeDuration(DurationType(4, 5), DurationType(2, 3)) == DurationType(2, 5));

	OnlineDetector on1(1, 10);
	on1.AddOnlineDuration(DurationType(0, 4));
	on1.AddOnlineDuration(DurationType(2, 8));
	on1.AddOnlineDuration(DurationType(8, 10));
	on1.Merge();
	assert(on1.IsOnline());
	assert(on1.GetRecoveryState() == OnlineDetector::RECOVERY_STATE_ONLINE);

	OnlineDetector on2(2, 8);
	on2.AddOnlineDuration(DurationType(3, 4));
	on2.Merge();
	assert(on2.IsOnline() == false);
	assert(on2.GetRecoveryState() == OnlineDetector::RECOVERY_STATE_UNKNOWN);

	OnlineDetector on3(3, 9);
	on3.AddOnlineDuration(DurationType(1, 12));
	on3.Merge();
	assert(on3.IsOnline());
	assert(on3.GetRecoveryState() == OnlineDetector::RECOVERY_STATE_ONLINE);

	OnlineDetector on4(1, 9);
	on4.AddOnlineDuration(DurationType(1, 6));
	on4.Merge();
	assert(on4.GetRecoveryState() == OnlineDetector::RECOVERY_STATE_UN_RECOVERY);

	OnlineDetector on5(1, 9);
	on5.AddOnlineDuration(DurationType(1, 6));
	on5.AddOnlineDuration(DurationType(8, 9));
	on5.Merge();
	assert(on5.GetRecoveryState() == OnlineDetector::RECOVERY_STATE_RECOVERY);
}



int main()
{


	return 0;
}