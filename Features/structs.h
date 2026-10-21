enum class ECompetitiveTier : uint8_t
{
	ECompetitiveTier__Iron1 = 3,
	ECompetitiveTier__Iron2 = 4,
	ECompetitiveTier__Iron3 = 5,
	ECompetitiveTier__Bronze1 = 6,
	ECompetitiveTier__Bronze2 = 7,
	ECompetitiveTier__Bronze3 = 8,
	ECompetitiveTier__Silver1 = 9,
	ECompetitiveTier__Silver2 = 10,
	ECompetitiveTier__Silver3 = 11,
	ECompetitiveTier__Gold1 = 12,
	ECompetitiveTier__Gold2 = 13,
	ECompetitiveTier__Gold3 = 14,
	ECompetitiveTier__Platinum1 = 15,
	ECompetitiveTier__Platinum2 = 16,
	ECompetitiveTier__Platinum3 = 17,
	ECompetitiveTier__Diamond1 = 18,
	ECompetitiveTier__Diamond2 = 19,
	ECompetitiveTier__Diamond3 = 20,
	ECompetitiveTier__Immortal1 = 21,
	ECompetitiveTier__Immortal2 = 22,
	ECompetitiveTier__Immortal3 = 23,
	ECompetitiveTier__Radiant = 24,
	ECompetitiveTier_MAX = 25
};



struct TArrayE
{
	uint64_t data;
	uint32_t count;
	uint32_t max;
};

template<class Template>
class TArray
{
public:
	int Length() const
	{
		return Count;
	}

	Template GetById(std::int32_t Iteration)
	{
		return driver::read<Template>(Data + Iteration * sizeof(Template));
	}

protected:
	std::uint64_t Data;
	std::uint32_t Count;
};

struct FLinearColorE
{
	float R;
	float G;
	float B;
	float A;
};

struct flinearcolor
{
	float r, g, b, a;
	flinearcolor() : r(0), g(0), b(0), a(0) {}
	flinearcolor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	flinearcolor(float r, float g, float b) : r(r), g(g), b(b), a(1.f) {}
};

namespace crt
{
	inline size_t strlen(const char* str) {
		if (str == nullptr) {
			return 0;
		}

		const char* s = str;
		while (*s != '\0') {
			++s;
		}
		return s - str;
	}

	inline int wcslen(const wchar_t* str) {
		int counter = 0;
		if (!str)
			return 0;
		for (; *str != '\0'; ++str)
			++counter;
		return counter;
	}

	inline int wcsicmp_insensitive(wchar_t* cs, wchar_t* ct) {
		auto len = wcslen(cs);
		if (len != wcslen(ct))
			return false;

		for (size_t i = 0; i < len; i++)
			if ((cs[i] | L' ') != (ct[i] | L' '))
				return false;

		return true;
	}

	__forceinline bool contains(std::string firstString, std::string secondString) {
		if (secondString.size() > firstString.size())
			return false;

		for (int i = 0; i < firstString.size(); i++) {
			int j = 0;
			if (firstString[i] == secondString[j]) {
				int k = i;
				while (firstString[i] == secondString[j] && j < secondString.size()) {
					j++;
					i++;
				}
				if (j == secondString.size())
					return true;
				else
					i = k;
			}
		}
		return false;
	}
}

template <class type>
struct tarray {
public:
	tarray() { this->data = nullptr; this->count = this->max = 0; };

	type* data;
	std::int32_t count, max;

	type& operator[](int i) {
		return this->data[i];
	};

	int size() {
		return this->count;
	}

	bool valid(int i) {
		return bool(i < this->count);
	}
};
class fstring : public tarray<wchar_t>
{
public:
	inline fstring()
	{
	};

	fstring(const wchar_t* other)
	{
		max = count = *other ? static_cast<int>(crt::wcslen(other)) + 1 : 0;

		if (count)
		{
			data = const_cast<wchar_t*>(other);
		}
	};

	fstring(const wchar_t* other, int _count)
	{
		data = const_cast<wchar_t*>(other);
		max = count = _count;
	};

	bool is_valid() const
	{
		return data != nullptr;
	}

	const wchar_t* wide() const
	{
		return data;
	}

	const wchar_t* c_str() const
	{
		return this->data;
	}

	std::string to_str() const
	{
		if (!data) return "";
		auto length = crt::wcslen(data);

		std::string str(length, '\0');

		for (size_t i = 0; i < length; ++i) {
			wchar_t wc = data[i];

			if (wc >= 0 && wc < 128) {
				str[i] = static_cast<char>(wc);
			}
			else {
				str[i] = '?';
			}
		}

		return str;
	}

	std::wstring ToWString() const
	{
		if (!data || max <= 0) return std::wstring();
		int len = crt::wcslen(data);
		if (len <= 0) return std::wstring();
		return std::wstring(data, len);
	}

	std::string ToString2() const
	{
		return to_str();
	}


	std::string ToString() const
	{
		auto length = std::wcslen(data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(data, data + length, '?', &str[0]);

		return str;
	}

};