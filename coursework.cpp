#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "additional_code.cpp"

#define setwhite SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255)
#define setblack SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0)
#define drawrect SDL_RenderFillRect(renderer, &rect)
#define updateren SDL_RenderPresent(renderer)

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
SDL_Surface* surface = NULL;
SDL_Rect rect;
SDL_Rect rect_init;
SDL_Rect rect_test;
SDL_Rect rect_Iden;
SDL_Rect rect_Comp;
SDL_Rect rect_cnt;
SDL_Rect rect_str;
SDL_Rect rect_cntin;
SDL_Rect rect_strin;
SDL_Rect rect_num;
SDL_Rect rect_iden;
SDL_Rect rect_comp;
SDL_Rect rect_err;
SDL_Rect rect_again;
SDL_Rect rect_search;
SDL_Rect rect_minusid;
SDL_Rect rect_pluscomp;
SDL_Rect rect_minuscomp;
SDL_Rect rect_res;
SDL_Rect rect_res_;
SDL_Event event;
SDL_Color white = {255, 255, 255, 255};
SDL_Color black = {0, 0, 0, 0};
string cnt = "";
string* strs = NULL;

int width = 0;
int height = 0;
int num = 0;
int font_size = 0;

void reverse(char* s)
{
	int i, j;
	char c;
	for(i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
char* itoa_(int n)
{
	int i, sign;
	char s[1024];
	if((sign = n) < 0) n = -n;
	i = 0;
	do
	{
		s[i++] = n % 10 + '0';
	}
	while((n /= 10) > 0);
	if(sign < 0) s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	return s;
}
int atoi_(const char* s)
{
	int n = 0;
	while(*s >= '0' && *s <= '9')
	{
		n *= 10;
		n += *s++;
		n -= '0';
	}
	return n;
}
void line(double x1, double y1, double x2, double y2)
{
	SDL_RenderDrawLine(renderer, (int) x1, (int) y1, (int) x2, (int) y2);
}
void text(double x, double y, const char* text, int size, bool flag, SDL_Rect& rect)
{
	int w, h;
	TTF_Font* font = TTF_OpenFont("font.ttf", size);
	surface = TTF_RenderText_Solid(font, text, white);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	rect.x = x - w / 2;
	rect.y = y - h / 2;
	rect.w = w;
	rect.h = h;
	if(flag)
	{
		setwhite;
		line(rect.x, rect.y, rect.x + w, rect.y);
		line(rect.x, rect.y + h, rect.x + w, rect.y + h);
		line(rect.x, rect.y, rect.x, rect.y + h);
		line(rect.x + w, rect.y, rect.x + w, rect.y + h);
	}
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void refresh(int x, int y, int w, int h)
{
	setblack;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	drawrect;
}
void show()
{
	refresh(0, 0, width / 3, height / 3 * 2);
	int k = 0;
	char** nums;
	if(num == 0) text(width / 6, height / 12, "Empty", font_size, false, rect);
	else
	{
		nums = new char* [num];
		for(int i = 0; i < num; i++)
		{
			int w, h;
			string tmp = "";
			nums[i] = new char[3];
			if(i / 10 == 0)
			{
				nums[i][0] = ' ';
				nums[i][1] = i + '0';
				nums[i][2] = ')';
			}
			else
			{
				nums[i][0] = i / 10 + '0';
				nums[i][1] = i % 10 + '0';
				nums[i][2] = ')';
			}
			text(font_size, height / 12 + k, nums[i], font_size, false, rect);
			for(int kg = 0; kg <= (strs[i]).size() / 32; kg++)
			{
				for(int j = 1 * 32 * kg; j < 32 * (kg + 1) && strs[i][j]; j++) tmp += strs[i][j];
				TTF_Font* font = TTF_OpenFont("font.ttf", font_size);
				surface = TTF_RenderText_Solid(font, tmp.c_str(), white);
				texture = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_QueryTexture(texture, NULL, NULL, &w, &h);
				text(font_size * 2 + w / 2, height / 12 + k, tmp.c_str(), font_size, false, rect);
				tmp = "";
				k += font_size;
			}
		}
	}
}
void logs()
{

}
void start(bool flag)
{
	setwhite;
	line(width / 3, 0, width / 3, height);
	line(width / 3 * 2, 0, width / 3 * 2, height / 3 * 2);
	line(0, height / 3 * 2, width, height / 3 * 2);
	text(width / 2, height / 12, "Initialization", font_size, true, rect_init);
	text(width / 6 * 5, height / 12, "Testing", font_size, true, rect_test);
	show();
	if(flag) updateren;
}
void init()
{
	text(width / 2, height / 4, "Enter count", font_size, true, rect_cnt);
	text(width / 2, height / 4 + font_size * 1.5, "Enter strings", font_size, true, rect_str);
	updateren;
}
void test()
{
	refresh(rect_pluscomp.x, rect_pluscomp.y, rect_pluscomp.w + 1, rect_pluscomp.h + 1);
	refresh(rect_minuscomp.x, rect_minuscomp.y, rect_minuscomp.w + 1, rect_minuscomp.h + 1);
	updateren;
	text(width / 6 * 5, height / 4, "Identificator", font_size, true, rect_iden);
	text(width / 6 * 5, height / 4 + font_size * 1.5, "Complex", font_size, true, rect_comp);
	updateren;
}
bool loop(string& input, SDL_Rect& rectout)
{
	string tmp;
	TTF_Font* font = TTF_OpenFont("font.ttf", font_size);
	rect.x = rectout.x + rectout.w;
	rect.y = rectout.y;
	rect.w = 0;
	rect.h = font_size;
	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				return false;
			case SDL_TEXTINPUT:
				input += event.text.text;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_BACKSPACE && input.size()) input.pop_back();
				if(event.key.keysym.sym == SDLK_RETURN && input.size()) return false;
				break;
		}
	}
	if(input.size())
	{
		surface = TTF_RenderText_Solid(font, input.c_str(), white);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		rect.x = rectout.x + rectout.w;
		rect.y = rectout.y;
		rect.w = surface->w;
		rect.h = surface->h;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);

	}
	while(event.type != SDL_KEYDOWN && event.key.keysym.sym != SDLK_RETURN);
	{
		setwhite;
		line(rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + font_size);
		updateren;
		SDL_Delay(300);
		setblack;
		line(rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + font_size);
		updateren;
		SDL_Delay(300);
	}
	return true;
}
bool is_digits(string str)
{
	if(str == "") return false;
	for(int i = 0; i < str.size(); i++)
		if((str[i] ^ '0') > 9) return false;
	return true;
}
void input_count()
{
	refresh(rect_Iden.x, rect_Iden.y, rect_Iden.w + 1, rect_Iden.h + 1);
	refresh(rect_Comp.x, rect_Comp.y, rect_Comp.w + 1, rect_Comp.h + 1);
	if(num > 0)
	{
		text(width / 2, height / 9 * 7 + font_size * 1.5, "Error, count > 0", font_size, false, rect_err);
		updateren;
	}
	else
	{
		text(width / 2 - font_size * 7, height / 9 * 7 + font_size * 1.5, "Input count:", font_size, false, rect_cntin);
		updateren;
		SDL_StartTextInput();
		while(loop(cnt, rect_cntin)) refresh(rect.x, rect.y, rect.w, rect.h);
		while(is_digits(cnt) == false)
		{
			text(rect_cntin.x + rect_cntin.w * 1.5, height / 9 * 7, "Again, please", font_size, false, rect_again);
			updateren;
			cnt = "";
			while(loop(cnt, rect_cntin)) refresh(rect.x, rect.y, rect.w, rect.h);
		};
		num = atoi(cnt.c_str());
		SDL_StopTextInput();
	}
	strs = new string[num];
	refresh(rect_cntin.x, rect_cntin.y, rect_cntin.w, rect_cntin.h);
	refresh(rect_again.x, rect_again.y, rect_again.w, rect_again.h);
	refresh(rect_err.x, rect_err.y, rect_err.w, rect_err.h);
	updateren;
}
void input_string()
{
	text(width / 2, height / 2, "Identificator", font_size, true, rect_Iden);
	text(width / 2, height / 2 + font_size * 1.5, "Complex", font_size, true, rect_Comp);
	updateren;
}
void string_(char str[], int& k)
{
	int i = 0;
	if(num == 0)
	{
		text(width / 2, height / 9 * 7 + font_size * 1.5, "Error, count = 0", font_size, false, rect_err);
		updateren;
		refresh(rect_err.x, rect_err.y, rect_err.w, rect_err.h);
	}
	else
	{
		string numb = "";
		SDL_StartTextInput();
		text(width / 2 - font_size * 6.5, height / 9 * 7 + font_size * 1.5, "Input number:", font_size, false, rect_strin);
		updateren;
		while(loop(numb, rect_strin)) refresh(rect.x, rect.y, rect.w, rect.h);
		while(is_digits(numb) == false || atoi(numb.c_str()) >= num || atoi(numb.c_str()) < 0)
		{
			text(rect_strin.x + rect_strin.w * 1.5, height / 9 * 7, "Again, please", font_size, false, rect_again);
			updateren;
			numb = "";
			while(loop(numb, rect_strin)) refresh(rect.x, rect.y, rect.w, rect.h);
		};
		refresh(rect_strin.x, rect_strin.y, rect_strin.w, rect_strin.h);
		refresh(rect_err.x, rect_err.y, rect_err.w, rect_err.h);
		refresh(rect_again.x, rect_again.y, rect_again.w, rect_again.h);
		k = atoi(numb.c_str());
		text(width / 2 - font_size * 6.5, height / 9 * 7 + font_size * 1.5, "Input string:", font_size, false, rect_strin);
		updateren;
		while(loop(strs[k], rect_strin)) refresh(rect.x, rect.y, rect.w, rect.h);
		refresh(rect_strin.x, rect_strin.y, rect_strin.w, rect_strin.h);
		refresh(rect_err.x, rect_err.y, rect_err.w, rect_err.h);
		SDL_StopTextInput();
		show();
		updateren;
	}
}
void iden()
{
	refresh(rect_pluscomp.x, rect_pluscomp.y, rect_pluscomp.w + 1, rect_pluscomp.h + 1);
	refresh(rect_minuscomp.x, rect_minuscomp.y, rect_minuscomp.w + 1, rect_minuscomp.h + 1);
	text(width / 6 * 5, height / 2, "Search symbol", font_size, true, rect_search);
	text(width / 6 * 5, height / 2 + font_size * 1.5, "Subtraction", font_size, true, rect_minusid);
	updateren;
}
void comp()
{
	refresh(rect_search.x, rect_search.y, rect_search.w + 1, rect_search.h + 1);
	refresh(rect_minusid.x, rect_minusid.y, rect_minusid.w + 1, rect_minusid.h + 1);
	text(width / 6 * 5, height / 2, "Addition", font_size, true, rect_pluscomp);
	text(width / 6 * 5, height / 2 + font_size * 1.5, "Subtraction", font_size, true, rect_minuscomp);
	updateren;
}
void search(int& indexx, char& symboll)
{
	string index, symbol;
	text(width / 6 * 5 - font_size * 6, height / 9 * 7 + font_size, "Input number:", font_size, false, rect_num);
	SDL_StartTextInput();
	while(loop(index, rect_num)) refresh(rect.x, rect.y, rect.w, rect.h);
	while(is_digits(index) == false)
	{
		text(width / 6 * 5 + font_size, height / 9 * 7, "Again, please", font_size, false, rect_again);
		updateren;
		index = "";
		while(loop(index, rect_num)) refresh(rect.x, rect.y, rect.w, rect.h);
	};
	indexx = atoi_(index.c_str());
	refresh(rect_num.x, rect_num.y, rect_num.w + 1, rect_num.h + 1);
	refresh(rect.x, rect.y, rect.w + 1, rect.h + 1);
	refresh(rect_again.x, rect_again.y, rect_again.w + 1, rect_again.h + 1);
	text(width / 6 * 5 - font_size * 6, height / 9 * 7 + font_size, "Input symbol:", font_size, false, rect_num);
	while(!(event.type != SDL_KEYDOWN && event.key.keysym.sym != SDLK_RETURN)) loop(symbol, rect_num);
	SDL_StopTextInput();
	symboll = symbol[0];
	refresh(rect_num.x, rect_num.y, rect_num.w + 21, rect_num.h + 1);
	refresh(rect.x, rect.y, rect.w + 1, rect.h + 1);
	refresh(rect_again.x, rect_again.y, rect_again.w + 1, rect_again.h + 1);
	updateren;
}
void plusminus(int& fnum, int& snum)
{
	string num1, num2;
	text(width / 6 * 5 - font_size * 4, height / 9 * 7 + font_size, "Input first number:", font_size, false, rect_num);
	SDL_StartTextInput();
	while(loop(num1, rect_num)) refresh(rect.x, rect.y, rect.w, rect.h);
	while(is_digits(num1) == false)
	{
		text(width / 6 * 5 + font_size * 5, height / 9 * 7, "Again, please", font_size, false, rect_again);
		updateren;
		num1 = "";
		while(loop(num1, rect_num)) refresh(rect.x, rect.y, rect.w, rect.h);
	};
	fnum = atoi(num1.c_str());
	SDL_StopTextInput();
	refresh(rect_num.x, rect_num.y, rect_num.w + 1, rect_num.h + 1);
	refresh(rect.x, rect.y, rect.w + 1, rect.h + 1);
	refresh(rect_again.x, rect_again.y, rect_again.w + 1, rect_again.h + 1);
	text(width / 6 * 5 - font_size * 4, height / 9 * 7 + font_size, "Input second number:", font_size, false, rect_num);
	updateren;
	SDL_StartTextInput();
	while(loop(num2, rect_num)) refresh(rect.x, rect.y, rect.w, rect.h);
	while(is_digits(num2) == false)
	{
		text(width / 6 * 5 + font_size * 5, height / 9 * 7, "Again, please", font_size, false, rect_again);
		updateren;
		num2 = "";
		while(loop(num2, rect_num)) refresh(rect.x, rect.y, rect.w, rect.h);
	};
	snum = atoi(num2.c_str());
	SDL_StopTextInput();
	refresh(rect_num.x, rect_num.y, rect_num.w + 1, rect_num.h + 1);
	refresh(rect.x, rect.y, rect.w + 1, rect.h + 1);
	refresh(rect_again.x, rect_again.y, rect_again.w + 1, rect_again.h + 1);
	updateren;

}
int sdlinit()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Can't init: " << SDL_GetError() << endl;
		return 1;
	}
	if(TTF_Init() != 0)
	{
		cout << "Can't init ttf: " << TTF_GetError() << endl;
		return 1;
	}
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	width = DM.w;
	height = DM.h;
	width = 1280;
	height = 720;
	font_size = (width + height) / 100;
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	return 0;
}
int quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_Quit();
	delete[]strs;
	return 0;
}
int main(int argc, char** args)
{
	int count_in_array = 0;
	StringMain** array_elements = new StringMain * [0];
	if(sdlinit() == 1)
	{
		quit();
		return 1;
	}
	int xMouse, yMouse;
	bool run = true, Finit, Ftest, Fcnt, Fstr, Fident, Fcomp, Fident_, Fcomp_;
	Finit = Ftest = Fcnt = Fstr = Fident = Fcomp = Fident_ = Fcomp_ = false;
	start(true);
	int i = 0;
	while(run)
	{
		while(SDL_PollEvent(&event) != NULL)
		{
			if(event.type == SDL_QUIT)
				run = false;
			if(event.type == SDL_KEYDOWN)
				if(event.key.keysym.sym == SDLK_ESCAPE)
					run = false;
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&xMouse, &yMouse);
				if(xMouse > rect_init.x && yMouse > rect_init.y && xMouse < rect_init.x + rect_init.w && yMouse < rect_init.y + rect_init.h)
				{
					refresh(rect_cnt.x, rect_cnt.y, rect_cnt.w + 1, rect_cnt.h + 1);
					refresh(rect_str.x, rect_str.y, rect_str.w + 1, rect_str.h + 1);
					refresh(rect_Iden.x, rect_Iden.y, rect_Iden.w + 1, rect_Iden.h + 1);
					refresh(rect_Comp.x, rect_Comp.y, rect_Comp.w + 1, rect_Comp.h + 1);
					init();
					Finit = true;
				}
				if(xMouse > rect_test.x && yMouse > rect_test.y && xMouse < rect_test.x + rect_test.w && yMouse < rect_test.y + rect_test.h)
				{
					refresh(rect_search.x, rect_search.y, rect_search.w + 1, rect_search.h + 1);
					refresh(rect_minusid.x, rect_minusid.y, rect_minusid.w + 1, rect_minusid.h + 1);
					refresh(rect_pluscomp.x, rect_pluscomp.y, rect_pluscomp.w + 1, rect_pluscomp.h + 1);
					refresh(rect_minuscomp.x, rect_minuscomp.y, rect_minuscomp.w + 1, rect_minuscomp.h + 1);
					test();
					Ftest = true;
				}
				if(xMouse > rect_cnt.x && yMouse > rect_cnt.y && xMouse < rect_cnt.x + rect_cnt.w && yMouse < rect_cnt.y + rect_cnt.h && Finit == true)
				{
					input_count();
					Fcnt = true;
					Fstr = false;
					array_elements = new StringMain * [num];
				}
				if(xMouse > rect_str.x && yMouse > rect_str.y && xMouse < rect_str.x + rect_str.w && yMouse < rect_str.y + rect_str.h && Finit == true)
				{
					input_string();
					Fstr = true;
					Fcnt = false;
				}
				if(xMouse > rect_Iden.x && yMouse > rect_Iden.y && xMouse < rect_Iden.x + rect_Iden.w && yMouse < rect_Iden.y + rect_Iden.h && Finit == true)
				{
					char* str;
					str = new char[1024];
					int k = 0;
					string_(str, k);
					strcpy_(str, strs[k].c_str());
					array_elements[k] = new StringIdentifier(str);
					Fident_ = true;
					Fstr = false;
				}
				if(xMouse > rect_Comp.x && yMouse > rect_Comp.y && xMouse < rect_Comp.x + rect_Comp.w && yMouse < rect_Comp.y + rect_Comp.h && Finit == true)
				{
					char* str;
					str = new char[1024];
					int k = 0;
					string_(str, k);
					strcpy_(str, strs[k].c_str());
					array_elements[k] = new StringComplex(str);
					Fcomp_ = true;
					Fstr = false;
				}
				if(xMouse > rect_iden.x && yMouse > rect_iden.y && xMouse < rect_iden.x + rect_iden.w && yMouse < rect_iden.y + rect_iden.h && Ftest == true)
				{
					iden();
					Fident = true;
					Fcomp = false;
				}
				if(xMouse > rect_comp.x && yMouse > rect_comp.y && xMouse < rect_comp.x + rect_comp.w && yMouse < rect_comp.y + rect_comp.h && Ftest == true)
				{
					comp();
					Fcomp = true;
					Fident = false;
				}
				if(xMouse > rect_search.x && yMouse > rect_search.y && xMouse < rect_search.x + rect_search.w && yMouse < rect_search.y + rect_search.h && Ftest == true && Fident == true)
				{
					int index;
					char symbol;
					char* res;
					res = new char[1024];
					int res_ = 0;
					search(index, symbol);
					text(width / 6 * 5 - font_size * 8, height / 9 * 7 + font_size, "Result:", font_size, false, rect_res);
					updateren;
					res_ = (*(StringIdentifier*) array_elements[index]).Search(symbol);
					res = itoa_(res_);
					text(width / 6 * 5 - font_size * 8 + rect_res.w / 2, height / 9 * 7 + font_size, res, font_size, false, rect_res_);
					updateren;
					refresh(rect_res.x, rect_res.y, rect_res.w, rect_res.h);
					refresh(rect_res_.x, rect_res_.y, rect_res_.w, rect_res_.h);
				}
				if(xMouse > rect_minusid.x && yMouse > rect_minusid.y && xMouse < rect_minusid.x + rect_minusid.w && yMouse < rect_minusid.y + rect_minusid.h && Ftest == true && Fident == true)
				{
					int fnum , snum ;
					char* res;
					res = new char[1024];
					int w, h;
					plusminus(fnum, snum);
					text(width / 6 * 5 - font_size * 8, height / 9 * 7 + font_size, "Result:", font_size, false, rect_res);
					updateren;
					res = (*(StringIdentifier*) array_elements[fnum]) - (*(StringIdentifier*) array_elements[snum]);
					TTF_Font* font = TTF_OpenFont("font.ttf", font_size);
					surface = TTF_RenderText_Solid(font, res, white);
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_QueryTexture(texture, NULL, NULL, &w, &h);
					text(rect_res.x + rect_res.w + w / 2, height / 9 * 7 + font_size, res, font_size, false, rect_res_);
					updateren;
					refresh(rect_res.x, rect_res.y, rect_res.w, rect_res.h);
					refresh(rect_res_.x, rect_res_.y, rect_res_.w, rect_res_.h);
				}
				if(xMouse > rect_pluscomp.x && yMouse > rect_pluscomp.y && xMouse < rect_pluscomp.x + rect_pluscomp.w && yMouse < rect_pluscomp.y + rect_pluscomp.h && Ftest == true && Fcomp == true)
				{
					int fnum, snum;
					char* res;
					int w, h;
					res = new char[1024];
					plusminus(fnum, snum);
					text(width / 6 * 5 - font_size * 8, height / 9 * 7 + font_size, "Result:", font_size, false, rect_res);
					updateren;
					res = (*(StringComplex*) array_elements[fnum]) + (*(StringComplex*) array_elements[snum]);
					TTF_Font* font = TTF_OpenFont("font.ttf", font_size);
					surface = TTF_RenderText_Solid(font, res, white);
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_QueryTexture(texture, NULL, NULL, &w, &h);
					text(rect_res.x + rect_res.w + w / 2, height / 9 * 7 + font_size, res, font_size, false, rect_res_);
					updateren;
					refresh(rect_res.x, rect_res.y, rect_res.w, rect_res.h);
					refresh(rect_res_.x, rect_res_.y, rect_res_.w, rect_res_.h);
				}
				if(xMouse > rect_minuscomp.x && yMouse > rect_minuscomp.y && xMouse < rect_minuscomp.x + rect_minuscomp.w && yMouse < rect_minuscomp.y + rect_minuscomp.h && Ftest == true && Fcomp == true)
				{
					int fnum, snum;
					char* res;
					int w, h;
					res = new char[1024];
					plusminus(fnum, snum);
					text(width / 6 * 5 - font_size * 8, height / 9 * 7 + font_size, "Result:", font_size, false, rect_res);
					updateren;
					res = (*(StringComplex*) array_elements[fnum]) - (*(StringComplex*) array_elements[snum]);
					TTF_Font* font = TTF_OpenFont("font.ttf", font_size);
					surface = TTF_RenderText_Solid(font, res, white);
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_QueryTexture(texture, NULL, NULL, &w, &h);
					text(rect_res.x + rect_res.w + w / 2, height / 9 * 7 + font_size, res, font_size, false, rect_res_);
					updateren;
					refresh(rect_res.x, rect_res.y, rect_res.w, rect_res.h);
					refresh(rect_res_.x, rect_res_.y, rect_res_.w, rect_res_.h);
				}
				if(!(xMouse > width / 3 && xMouse < width / 3 * 2 && yMouse > 0 && yMouse < height / 3 * 2) && Finit == true)
				{
					refresh(rect_cnt.x, rect_cnt.y, rect_cnt.w + 1, rect_cnt.h + 1);
					refresh(rect_str.x, rect_str.y, rect_str.w + 1, rect_str.h + 1);
					refresh(rect_Iden.x, rect_Iden.y, rect_Iden.w + 1, rect_Iden.h + 1);
					refresh(rect_Comp.x, rect_Comp.y, rect_Comp.w + 1, rect_Comp.h + 1);
					refresh(rect_err.x, rect_err.y, rect_err.w, rect_err.h);
					refresh(rect_again.x, rect_again.y, rect_again.w, rect_again.h);
					Finit = false;
					updateren;
				}
				if(!(xMouse > width / 3 * 2 && xMouse < width && yMouse > 0 && yMouse < height / 3 * 2) && Ftest == true)
				{
					refresh(rect_iden.x, rect_iden.y, rect_iden.w + 1, rect_iden.h + 1);
					refresh(rect_comp.x, rect_comp.y, rect_comp.w + 1, rect_comp.h + 1);
					refresh(rect_search.x, rect_search.y, rect_search.w + 1, rect_search.h + 1);
					refresh(rect_minusid.x, rect_minusid.y, rect_minusid.w + 1, rect_minusid.h + 1);
					refresh(rect_pluscomp.x, rect_pluscomp.y, rect_pluscomp.w + 1, rect_pluscomp.h + 1);
					refresh(rect_minuscomp.x, rect_minuscomp.y, rect_minuscomp.w + 1, rect_minuscomp.h + 1);
					refresh(rect_res.x, rect_res.y, rect_res.w, rect_res.h);
					refresh(rect_res_.x, rect_res_.y, rect_res_.w, rect_res_.h);
					Ftest = false;
					updateren;
				}
			}
		}
	}
	return quit();
}