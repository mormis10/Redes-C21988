#include <algorithm>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Subnetting{
    public:
    Subnetting();
    void set_values_from_file(std::string file_name);
    void print_values_prove();
    void menu();
    int get_needed_sols(int sols, int& power);
    int get_mask(int power);
    void make_calc();
    void send_prove(bool option);
    void sort_ranges_upper(std::vector<int>& sols_ , std::vector<char>& ranges_);
    void sort_ranges_lower(std::vector<int>& sols_ , std::vector<char>& ranges_);
    void prove();
    void subnetting_menu();
    void safe_data_on_file(const char range,const int mask, const std::string net_id,std::string first_avaible_direction, std::string last_avaible_direction, std::string brodcast);
    void clear_vectors(std::vector<int>& sols, std::vector<char>& ranges, std::vector<int>& masks);
    void get_ip_ready_lower_upper(int sols_total);
    int calc_sol_total_size();
    private:
    std::string base_ip;
    int work_ip[4] = {0,0,0,0};
    std::vector<int> sols;
    std::vector<char> ranges;
    std::vector<int>masks;
    std::string files[6];
    int ranges_count;
};