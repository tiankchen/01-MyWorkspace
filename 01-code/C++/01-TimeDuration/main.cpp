

#include <iostream>
#include <vector>
#include <map>

#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>


class OnlineDetector
{
public:
	//ʱ���<��ʼʱ�䣬����ʱ��>��������
	typedef std::pair<time_t, time_t>		DurationType;

	//<��ʼʱ��-ʱ���>ӳ���
	typedef std::map<time_t, DurationType>		DurationMapType;
	typedef DurationMapType::iterator				IteratorType;
	typedef DurationMapType::const_iterator		ConstIteratorType;

	enum RecoveryState
	{
		RECOVERY_STATE_ONLINE,				//һֱ����
		RECOVERY_STATE_UN_RECOVERY,	//δ�ظ�
		RECOVERY_STATE_RECOVERY,			//�ѻָ�
		RECOVERY_STATE_UNKNOWN,			//δ֪
	};

public:
	OnlineDetector()
		: m_begin(0)
		, m_end(0)
		, m_durations()
	{}

	//�����ڼ�Ŀ�ʼʱ��ͽ���ʱ��
	OnlineDetector(time_t begin, time_t end)
		: m_begin(begin)
		, m_end(end)
		, m_durations()
	{}

	/**
	 * @brief ��������ʱ���
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
	 * @�ж�����ʱ����Ƿ��Ѿ���������������
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
	 * @brief ��ȡ��ǰʱ��λָ�״̬
	 */
	int GetRecoveryState() const
	{
		bool onlineOnBegin = false;		//��ʼʱ�������
		bool onlineOnEnd = false;			//����ʱ�������
		bool hasBreak = false;				//�ڹ涨ʱ������м��

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
			
			//�ж���һ��ʱ����뵱ǰʱ��֮��Ŀհף��Ƿ���������
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
	 * @brief ������ʱ��μ��Ͻ�������ϲ�
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
				break;		//it��ָΪ���һ����Чʱ���
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
	 * @brief �ж�����ʱ���֮���Ƿ��н���
	 */
	bool HasIntersection(const DurationType& d1, const DurationType& d2) const
	{
		//�ж�����������һά�������Ϸֲ�
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
			return true;	//���������ĵ�һ�������ڿ��������У����ཻ
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief �ϲ�����ʱ���
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
	DurationMapType m_durations;	//�����֮���໥����
};

/**
 * @brief ����ʱ����Ƿ��ཻ
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