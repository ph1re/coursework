#include <string>

using namespace std;

char* strcpy_(char* dst, const char* src)
{
	while((*dst++ = *src++) != '\0');
	return dst;
}

class StringMain //������� ����� �������
{
	static int counter_; //���������� ������� ������������ �����������
protected:
	char* pointer_; //��������� �� ���� ����������� ���������� ������ ��� ���������� �������� ������
	int length_; //����� ������ � ������
public:
	StringMain() //����������� ��� ����������
	{
		cout << "StringMain()" << endl; //������ ���������
		length_ = 0; //��������� �����
		pointer_ = new char; //��������� ������ ��� ������������ ����
		pointer_[length_] = '\0'; //�������� ������ ������
	}
	StringMain(const char* other) //�����������, ����������� � �������� ��������� ��-������
	{
		cout << "StringMain(const char* other)" << endl; //������ ���������
		length_ = strlen(other); //������������ ����� �������� ������
		pointer_ = new char[length_ + 1]; //��������� ������ ��� ����� ������
		strcpy_(pointer_, other); //����������� �������� ������ �� ����� ����� ������
		pointer_[length_] = '\0'; //��������� ������
	}
	StringMain(const StringMain& other) //����������� �����������
	{
		cout << "StringMain(const StringMain& other)" << endl; //������ ���������
		cout << "�� ��� ������ " << ++counter_ << " ���" << endl; //������ ���������� ��� �������
		length_ = other.length_; //������������ ����� �������� ������
		pointer_ = new char[length_ + 1]; //��������� ������ ��� ����� ������
		strcpy_(pointer_, other.pointer_); //����������� �������� ������ �� ����� ����� ������
		pointer_[length_] = '\0'; //��������� ������
	}
	~StringMain() //����������
	{
		cout << "~StringMain()" << endl; //������ ���������
		if(length_ != 0)
		{
			delete[] pointer_; //�������� ������ ��� ������, ���� � ��� ���-�� ����
			length_ = 0;
		}
	}
	StringMain& operator=(const StringMain& other) //���������� �������� ������������ �=�
	{
		cout << "StringMain& operator=(const StringMain& other)" << endl; //������ ���������;
		if(length_ != 0)
			delete[] pointer_; //�������� ������ ��� ������, ���� � ��� ���-�� ����
		length_ = other.length_; //������������ ����� �������� ������
		pointer_ = new char[length_ + 1]; //��������� ������ ��� ����� ������
		strcpy_(pointer_, other.pointer_); //����������� �������� ������ �� ����� ����� ������
		return *this;
	}
	StringMain(const char other) //�����������, ����������� � �������� ��������� ������ (char)
	{
		cout << "StringMain(const char other)" << endl; //������ ���������
		pointer_ = new char[2]; //�������� ������ ��� �������� ������ � ������������ ����
		pointer_[0] = other; //������������ �������
		length_ = 1; //������ ����� 1
		pointer_[length_] = '\0'; //��������� ������
	}
	friend ostream& operator<< (ostream& out, const StringMain& p);
};

ostream& operator<<(ostream& out, const StringMain& p)
{
	out << p.pointer_;
	return out;
}

class StringIdentifier: public StringMain //����������� �� ������� ����� �������, ����� �������-�������������
{
	static int counter_; //���������� ������� ������������ �����������
public:
	int Check_Identifier() //������� �������������
	{
		cout << "Check_Identifier()" << endl; //������ ���������
		for(int i = 0; i < length_; i++)
			if(!(pointer_[i] >= 'a' && pointer_[i] <= 'z' || pointer_[i] >= 'A' && pointer_[i] <= 'Z' || pointer_[i] == '_'
				 || pointer_[i] >= '0' && pointer_[i] <= '9')) //�������� �� ����������� �������
				return 0; //��������� ������ �������-�������������
		if(pointer_[0] >= '0' && pointer_[0] <= '9') //�������� ������� �������
			return 0; //��������� ������ �������-�������������
		else
			return 1; //������ ������ ������������� �������
	}
	StringIdentifier(): StringMain() //����������� ��� ����������
	{
		cout << "StringIdentifier() : StringMain()" << endl; //������ ���������
	}
	StringIdentifier(const char* other): StringMain(other) //�����������, ����������� � �������� ��������� ��-������
	{
		cout << "StringIdentifier(const char* other) : StringMain(other)" << endl; //������ ���������
		if(!Check_Identifier())
		{
			if(length_ != 0)
				delete[] pointer_; //�������� ������ ��� ������, ���� � ��� ���-�� ����
			length_ = 0; //��������� �����
			pointer_ = new char; //��������� ������ ��� ������������ ����
			pointer_[length_] = '\0'; //�������� ������ ������
		}
	}
	StringIdentifier(const StringIdentifier& other) //����������� �����������
	{
		cout << "StringIdentifier(const StringIdentifier& other)" << endl; //������ ���������
		cout << "�� ��� ������ " << ++counter_ << " ���" << endl; //������ ���������� ��� �������
		length_ = other.length_; //������������ ����� �������� ������
		pointer_ = new char[length_ + 1]; //��������� ������ ��� ����� ������
		strcpy_(pointer_, other.pointer_); //����������� �������� ������ �� ����� ����� ������
		pointer_[length_] = '\0'; //��������� ������ 
	}
	~StringIdentifier() //����������
	{
		cout << "~StringIdentifier()" << endl; //������ ���������
		if(length_ != 0)
		{
			delete[] pointer_; //�������� ������ ��� ������, ���� � ��� ���-�� ����
			length_ = 0;
		}
	}
	StringIdentifier& operator=(const StringIdentifier& other) //���������� �������� ������������ �=�
	{
		cout << "StringIdentifier& operator=(const StringIdentifier& other)" << endl; //������ ���������;
		if(length_ != 0)
			delete[] pointer_; //�������� ������ ��� ������, ���� � ��� ���-�� ����
		length_ = other.length_; //������������ ����� �������� ������
		pointer_ = new char[length_ + 1]; //��������� ������ ��� ����� ������
		pointer_[0] = '\0'; //�������� ������ ������
		strcpy_(pointer_, other.pointer_); //����������� �������� ������ �� ����� ����� ������
		pointer_[length_] = '\0'; //��������� ������
		return *this;
	}
	StringIdentifier(const char other):StringMain(other) //�����������, ����������� � �������� ��������� ������ (char)
	{
		cout << "StringIdentifier(const char other) :StringMain(other)" << endl; //������ ���������
		if(!Check_Identifier())
		{
			if(length_ != 0)
				delete[] pointer_; //�������� ������ ��� ������, ���� � ��� ���-�� ����
			length_ = 0; //��������� �����
			pointer_ = new char; //��������� ������ ��� ������������ ����
			pointer_[length_] = '\0'; //�������� ������ ������
		}
	}
	int Search(const char other) //����� ������� ��������� ������� � ������
	{
		cout << "Search(const char other)" << endl; //������ ���������
		int i, flag = -1;
		for(i = 0; i < length_; i++)
			if(pointer_[i] == other)
			{
				flag = i; //���� �������� �������� ������, �� ��������� ��� ����� � ������
				break; //������� �� �����
			}
		return flag + 1; //���������� �����
	}
	char* operator-(StringIdentifier& other) //��������������� �������� ��������� �-�
	{
		cout << "operator-(StringIdentifier& other)" << endl; //������ ���������
		char* result = new char[length_ + 1]; //��������� ������ ������-���������
		int i, j, end_str = 0;
		for(i = 0; i < length_; i++)
		{
			for(j = 0; j < other.length_ && pointer_[i] != other.pointer_[j]; j++);
			if(j == other.length_)
				result[end_str++] = pointer_[i]; //���������� ������ � ������-���������
		}
		result[end_str] = '\0'; //��������� ������
		return result;
	}
};

class StringComplex: public StringMain //����������� �� ������� ����� �������, ����� ������������ �����
{
	static int counter_; //���������� ������� ������������ �����������
public:
	StringComplex(): StringMain() //����������� ��� ����������
	{
		cout << "StringComplex() : StringMain()" << endl; //������ ���������
	}
	StringComplex(const char* other): StringMain(other) //�����������, ����������� � �������� ��������� ��-������
	{
		cout << "StringComplex(const char* other) : StringMain(other)" << endl; //������ ���������
		length_ = strlen(other); //������������ ����� �������� ������
		pointer_ = new char[length_ + 1]; //��������� ������ ��� ����� ������
		strcpy_(pointer_, other); //����������� �������� ������ �� ����� ����� ������
		pointer_[length_] = '\0'; //��������� ������
	}
	StringComplex(const StringComplex& other) //����������� �����������
	{
		cout << "StringComplex(const StringComplex& other)" << endl; //������ ���������
		cout << "�� ��� ������ " << ++counter_ << " ���" << endl; //������ ���������� ��� �������
		length_ = other.length_; //������������ ����� �������� ������
		pointer_ = new char[length_ + 1]; //��������� ������ ��� ����� ������
		strcpy_(pointer_, other.pointer_); //����������� �������� ������ �� ����� ����� ������
		pointer_[length_] = '\0'; //��������� ������ 
	}
	~StringComplex() //����������
	{
		cout << "~StringComplex()" << endl; //������ ���������
		if(length_ != 0)
		{
			delete[] pointer_; //�������� ������ ��� ������, ���� � ��� ���-�� ����
			length_ = 0;
		}
	}
	StringComplex& operator=(const StringComplex& other) //���������� �������� ������������ �=�
	{
		cout << "StringComplex& operator=(const StringComplex& other)" << endl; //������ ���������;
		length_ = other.length_; //������������ ����� �������� ������
		pointer_ = new char[length_ + 1]; //��������� ������ ��� ����� ������
		pointer_[0] = '\0'; //�������� ������ ������
		strcpy_(pointer_, other.pointer_); //����������� �������� ������ �� ����� ����� ������
		pointer_[length_] = '\0'; //��������� ������
		return *this;
	}
	int complong(int lena, int lenb, int* a, int* b)
	{
		cout << "complong(int lena, int lenb, int* a, int* b)" << endl; //������ ���������;
		if(lena < lenb)
			return -1;
		if(lena > lenb)
			return 1;
		for(int i = lena; i >= 1; i--)
		{
			if(a[i] < b[i])
				return -1;
			if(a[i] > b[i])
				return 1;
		}
		return 0;
	}
	char* slozjenie(char* first, char* second)
	{
		cout << "slozjenie(char* first, char* second)" << endl; //������ ���������;
		int lena;
		lena = strlen(first);
		int a[10000];
		for(int i = 0; i < lena; i++)
			a[lena - i] = int(first[i]) - 48;
		int lenb;
		lenb = strlen(second);
		int b[10000];
		for(int i = 0; i < lenb; i++)
			b[lenb - i] = int(second[i]) - 48;
		int maxx = max(lena, lenb);
		char* result = new char[maxx];
		if(maxx == lena)
			for(int i = lenb + 1; i <= lena; i++)
				b[i] = 0;
		else
			for(int i = lena + 1; i <= lenb; i++)
				a[i] = 0;
		int c = 0;
		for(int i = 1; i <= maxx; ++i)
			c = c + a[i] + b[i],
			a[i] = c % 10,
			c = c / 10;
		if(c > 0)
		{
			maxx++;
			a[maxx] = c;
		}
		int i = maxx;
		int j = 0;
		for(; i >= 1;)
			result[j++] = a[i--] + '0';
		i = 0;
		while(result[i] == '+' || result[i] == '-' || result[i] >= '0' && result[i] <= '9') i++;
		result[i] = '\0';
		return result;
	}
	char* vychitanie(char* first, char* second, int& flag)
	{
		cout << "vychitanie(char* first, char* second, int& flag)" << endl; //������ ���������;
		int lena;
		lena = strlen(first);
		int a[10000];
		for(int i = 0; i < lena; i++)
			a[lena - i] = int(first[i]) - 48;
		int lenb;
		lenb = strlen(second);
		int b[10000];
		for(int i = 0; i < lenb; i++)
			b[lenb - i] = int(second[i]) - 48;
		int maxx = max(lena, lenb);
		char* result = new char[maxx];
		if(maxx == lena)
			for(int i = lenb + 1; i <= lena; i++)
				b[i] = 0;
		else
			for(int i = lena + 1; i <= lenb; i++)
				a[i] = 0;
		if(complong(lena, lenb, a, b) < 0)
		{
			flag++;
			for(int i = 1; i <= maxx; ++i)
				swap(a[i], b[i]);
		}
		int c = 0;
		for(int i = 1; i <= maxx; ++i)
		{
			c = c + a[i] - b[i] + 10;
			a[i] = c % 10;
			if(c <= 9)c = -1;
			else c = 0;
		}
		while(a[maxx] == 0 && maxx > 1)
			maxx--;
		int j = 0;
		for(int i = maxx; i >= 1; i--)
			result[j++] = a[i] + '0';
		j = 0;
		while(result[j] == '+' || result[j] == '-' || result[j] >= '0' && result[j] <= '9') j++;
		result[j] = '\0';
		return result;
	}
	void Real_Imag(char* real, char* imag, StringComplex& other)
	{
		cout << "Real_Imag(char* real, char* imag, StringComplex& other)" << endl; //������ ���������;
		int i = 0;
		for(i; i < other.length_; i++)
		{
			if(other.pointer_[i] == 'i')
				break;
		}
		if(i == other.length_)
		{
			if(other.pointer_[0] == '+')
			{
				for(int j = 1; j < other.length_; j++)
					real[j] = other.pointer_[j];
			}
			for(int j = 0; j < other.length_; j++)
				real[j] = other.pointer_[j];
		}
		else if(i != other.length_)
		{
			if(other.pointer_[0] == '-' || other.pointer_[0] >= '0' && other.pointer_[0] <= '9')
			{
				int k = 0;
				for(int j = 0; j < i; j++)
					imag[j] = other.pointer_[j];
				for(int j = i + 1; j < other.length_; j++)
					real[k++] = other.pointer_[j];
			}
			else if(other.pointer_[0] == '+')
			{
				int k = 0;
				for(int j = 1; j < i; j++)
					imag[j] = other.pointer_[j];
				for(int j = i + 1; j < other.length_; j++)
					real[k++] = other.pointer_[j];
			}
		}
		i = 0;
		while(real[i] == 'i' || real[i] == '+' || real[i] == '-' || real[i] >= '0' && real[i] <= '9') i++;
		real[i] = '\0';
		i = 0;
		while(imag[i] == 'i' || imag[i] == '+' || imag[i] == '-' || imag[i] >= '0' && imag[i] <= '9') i++;
		imag[i] = '\0';
	}
	char* operator+(StringComplex& other) //��������������� �������� �������� �+�
	{
		cout << "operator+(StringComplex& other)" << endl; //������ ���������
		char* real_this = new char[1024];
		real_this[0] = '\0';
		char* imag_this = new char[1024];
		imag_this[0] = '\0';
		char* real_other = new char[1024];
		real_other[0] = '\0';
		char* imag_other = new char[1024];
		imag_other[0] = '\0';
		char* result = new char[1024];
		result[0] = '\0';
		Real_Imag(real_this, imag_this, *this);
		Real_Imag(real_other, imag_other, other);
		int i_pos = 0;
		if(imag_this[0] != '-' && imag_other[0] != '-')
		{
			result = slozjenie(imag_this, imag_other);
		}
		if(imag_this[0] != '-' && imag_other[0] == '-')
		{
			int flag = 0;
			int i = 0;
			while(imag_other[i] == '-' || imag_other[i] >= '0' && imag_other[i] <= '9')
			{
				imag_other[i] = imag_other[i + 1];
				i++;
			}
			result = vychitanie(imag_this, imag_other, flag);
			if(flag == 1)
			{
				i_pos++;
				for(i + 1; i > 0; i--)
					result[i] = result[i - 1];
				result[0] = '-';
			}
		}
		if(imag_this[0] == '-' && imag_other[0] != '-')
		{
			int flag = 0;
			int i = 0;
			while(imag_this[i] == '-' || imag_this[i] >= '0' && imag_this[i] <= '9')
			{
				imag_this[i] = imag_this[i + 1];
				i++;
			}
			result = vychitanie(imag_other, imag_this, flag);
			if(flag == 1)
			{
				i_pos++;
				for(i + 1; i > 0; i--)
					result[i] = result[i - 1];
				result[0] = '-';
			}
		}
		if(imag_this[0] == '-' && imag_other[0] == '-')
		{
			int i = 0;
			while(imag_other[i] == '-' || imag_other[i] >= '0' && imag_other[i] <= '9')
			{
				imag_other[i] = imag_other[i + 1];
				i++;
			}
			i = 0;
			while(imag_this[i] == '-' || imag_this[i] >= '0' && imag_this[i] <= '9')
			{
				imag_this[i] = imag_this[i + 1];
				i++;
			}
			result = slozjenie(imag_this, imag_other);
			i_pos++;
			for(i + 1; i > 0; i--)
				result[i] = result[i - 1];
			result[0] = '-';
		}
		if(result[0] != '\0')
		{
			while(result[i_pos] == '-' || result[i_pos] >= '0' && result[i_pos] <= '9')	i_pos++;
			result[i_pos] = 'i';
			result[i_pos + 1] = '\0';
			i_pos++;
		}
		if(real_this[0] != '-' && real_other[0] != '-')
		{
			char* dop = new char[1024];
			dop[0] = '\0';
			dop = slozjenie(real_this, real_other);
			int i = 0;
			while(dop[i] >= '0' && dop[i] <= '9')
			{
				result[i_pos++] = dop[i];
				i++;
			}
			result[i_pos] = '\0';
		}
		if(real_this[0] != '-' && real_other[0] == '-')
		{
			char* dop = new char[1024];
			dop[0] = '\0';
			int flag = 0;
			int i = 0;
			while(real_other[i] == '-' || real_other[i] >= '0' && real_other[i] <= '9')
			{
				real_other[i] = real_other[i + 1];
				i++;
			}
			dop = vychitanie(real_this, real_other, flag);
			if(flag == 1)
			{

				for(i + 1; i > 0; i--)
					dop[i] = dop[i - 1];
				dop[0] = '-';
			}
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')
			{
				result[i_pos++] = dop[i];
				i++;
			}
			result[i_pos] = '\0';
		}
		if(real_this[0] == '-' && real_other[0] != '-')
		{
			char* dop = new char[1024];
			dop[0] = '\0';
			int flag = 0;
			int i = 0;
			while(real_this[i] == '-' || real_this[i] >= '0' && real_this[i] <= '9')
			{
				real_this[i] = real_this[i + 1];
				i++;
			}
			dop = vychitanie(real_other, real_this, flag);
			if(flag == 1)
			{
				for(i + 1; i > 0; i--)
					dop[i] = dop[i - 1];
				dop[0] = '-';
			}
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')
			{
				result[i_pos++] = dop[i];
				i++;
			}
			result[i_pos] = '\0';
		}
		if(real_this[0] == '-' && real_other[0] == '-')
		{
			char* dop = new char[1024];
			dop[0] = '\0';
			int i = 0;
			while(real_other[i] == '-' || real_other[i] >= '0' && real_other[i] <= '9')
			{
				real_other[i] = real_other[i + 1];
				i++;
			}
			i = 0;
			while(real_this[i] == '-' || real_this[i] >= '0' && real_this[i] <= '9')
			{
				real_this[i] = real_this[i + 1];
				i++;
			}
			dop = slozjenie(real_this, real_other);
			for(i + 1; i > 0; i--)
				dop[i] = dop[i - 1];
			dop[0] = '-';
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')
			{
				result[i_pos++] = dop[i];
				i++;
			}
			result[i_pos] = '\0';
		}
		return result;
	}
	char* operator-(StringComplex& other) //��������������� �������� ��������� �-�
	{
		cout << "operator-(StringComplex& other)" << endl; //������ ���������
		char* real_this = new char[1024];
		real_this[0] = '\0';
		char* imag_this = new char[1024];
		imag_this[0] = '\0';
		char* real_other = new char[1024];
		real_other[0] = '\0';
		char* imag_other = new char[1024];
		imag_other[0] = '\0';
		char* result = new char[1024];
		result[0] = '\0';
		Real_Imag(real_this, imag_this, *this);
		Real_Imag(real_other, imag_other, other);
		int i_pos = 0;
		if(imag_this[0] != '-' && imag_other[0] != '-')
		{
			char* dop = new char[1024];
			dop[0] = '\0';
			int flag = 0;
			int i = 0;
			dop = vychitanie(imag_this, imag_other, flag);
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')	i++;
			if(flag == 1)
			{
				for(i + 1; i > 0; i--)
					dop[i] = dop[i - 1];
				dop[0] = '-';
			}
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')
			{
				result[i_pos++] = dop[i];
				i++;
			}
			result[i_pos] = '\0';
		}
		if(imag_this[0] != '-' && imag_other[0] == '-')
		{
			int i = 0;
			while(imag_other[i] == '-' || imag_other[i] >= '0' && imag_other[i] <= '9')
			{
				imag_other[i] = imag_other[i + 1];
				i++;
			}
			result = slozjenie(imag_this, imag_other);
		}
		if(imag_this[0] == '-' && imag_other[0] != '-')
		{
			int i = 0;
			while(imag_this[i] == '-' || imag_this[i] >= '0' && imag_this[i] <= '9')
			{
				imag_this[i] = imag_this[i + 1];
				i++;
			}
			result = slozjenie(imag_this, imag_other);
			while(result[i] == '-' || result[i] >= '0' && result[i] <= '9')	i++;
			for(i + 1; i > 0; i--)
				result[i] = result[i - 1];
			result[0] = '-';
		}
		if(imag_this[0] == '-' && imag_other[0] == '-')
		{
			int flag = 0;
			int i = 0;
			while(imag_this[i] == '-' || imag_this[i] >= '0' && imag_this[i] <= '9')
			{
				imag_this[i] = imag_this[i + 1];
				i++;
			}
			i = 0;
			while(imag_other[i] == '-' || imag_other[i] >= '0' && imag_other[i] <= '9')
			{
				imag_other[i] = imag_other[i + 1];
				i++;
			}
			result = vychitanie(imag_other, imag_this, flag);
			if(flag == 1)
			{
				i_pos++;
				for(i + 1; i > 0; i--)
					result[i] = result[i - 1];
				result[0] = '-';
			}
		}
		if(result[0] != '\0')
		{
			while(result[i_pos] == '-' || result[i_pos] >= '0' && result[i_pos] <= '9') i_pos++;
			result[i_pos] = 'i';
			result[i_pos + 1] = '\0';
			i_pos++;
		}
		if(real_this[0] != '-' && real_other[0] != '-')
		{
			char* dop = new char[1024];
			dop[0] = '\0';
			int flag = 0;
			int i = 0;
			dop = vychitanie(real_this, real_other, flag);
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')	i++;
			if(flag == 1)
			{
				for(i + 1; i > 0; i--)
					dop[i] = dop[i - 1];
				dop[0] = '-';
			}
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')
			{
				result[i_pos++] = dop[i];
				i++;
			}
			result[i_pos] = '\0';
		}
		if(real_this[0] != '-' && real_other[0] == '-')
		{
			char* dop = new char[1024];
			dop[0] = '\0';
			int i = 0;
			while(real_other[i] == '-' || real_other[i] >= '0' && real_other[i] <= '9')
			{
				real_other[i] = real_other[i + 1];
				i++;
			}
			dop = slozjenie(real_this, real_other);
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')
			{
				result[i_pos++] = dop[i];
				i++;
			}
			result[i_pos] = '\0';
		}
		if(real_this[0] == '-' && real_other[0] != '-')
		{
			int i = 0;
			char* dop = new char[1024];
			dop[0] = '\0';
			while(real_this[i] == '-' || real_this[i] >= '0' && real_this[i] <= '9')
			{
				real_this[i] = real_this[i + 1];
				i++;
			}
			dop = slozjenie(real_this, real_other);
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')	i++;
			for(i + 1; i > 0; i--)
				dop[i] = dop[i - 1];
			dop[0] = '-';
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')
			{
				result[i_pos++] = dop[i];
				i++;
			}
			result[i_pos] = '\0';
		}
		if(real_this[0] == '-' && real_other[0] == '-')
		{
			int flag = 0;
			int i = 0;
			char* dop = new char[1024];
			dop[0] = '\0';
			while(real_this[i] == '-' || real_this[i] >= '0' && real_this[i] <= '9')
			{
				real_this[i] = real_this[i + 1];
				i++;
			}
			i = 0;
			while(real_other[i] == '-' || real_other[i] >= '0' && real_other[i] <= '9')
			{
				real_other[i] = real_other[i + 1];
				i++;
			}
			dop = vychitanie(real_other, real_this, flag);
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')	i++;
			if(flag == 1)
			{
				for(i + 1; i > 0; i--)
					dop[i] = dop[i - 1];
				dop[0] = '-';
			}
			i = 0;
			while(dop[i] == '-' || dop[i] >= '0' && dop[i] <= '9')
			{
				result[i_pos++] = dop[i];
				i++;
			}
			result[i_pos] = '\0';
		}
		return result;
	}
};