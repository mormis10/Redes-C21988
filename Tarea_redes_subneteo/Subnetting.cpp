#include "Subnetting.hpp"

//Ojito para pruebas

Subnetting::Subnetting(){
std::ofstream file("Results.txt", std::ios::trunc);
this->files[0] = "Entrada0.txt";
this->files[1] = "Entrada1.txt";
this->files[2] = "Entrada2.txt";
this->files[3] = "Entrada3.txt";
this->files[4] = "Entrada4.txt";
this->files[5] = "Entrada5.txt";

}

void Subnetting::print_values_prove(){
    std::cout<<"Proves\n";
    std::cout<<this->base_ip <<"\n";
    for(int i = 0; i<this->ranges_count; i++){
        std::cout<<sols[i] <<"\n";;
        std::cout<<ranges[i] <<"\n";
    }
    std::cout<<"Enteros\n";

    for(int i = 0; i<4; i++){
      std::cout<<this->work_ip[i] <<" ";
    }

    std::cout<<"\n máscaras\n";
    for(int i = 0; i<this->ranges_count; i++){
        std::cout<<this->masks[i] <<" ";
    }

}

void Subnetting::set_values_from_file(std::string file_name){
     std::ifstream file(file_name);
     std::string line;
     if(!file.is_open()){
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
     }
     std::string temp;
     std::getline(file,line);
     std::istringstream ss(line);
     ss>>temp >>temp>> this->base_ip;
     std::istringstream ss1(base_ip);
     char clean_char;
     ss1>>this->work_ip[0] >>clean_char >> work_ip[1] >> clean_char >> work_ip[2] >> clean_char >> work_ip[3];
     std::getline(file,line);
     std::istringstream ss2(line);
     ss2>>temp >>temp >>temp >>this->ranges_count;
     file.ignore();
     char range_letter;
     int sols_size;
     char temp_char;
     for(int i = 0; i<this->ranges_count; i++){
        std::getline(file,line);
        std::istringstream ss(line);
        std::string temp;
        ss>>temp>>range_letter>> temp_char >>sols_size;
        this->ranges.push_back(range_letter);
        this->sols.push_back(sols_size);
     }

     file.close();

}


void Subnetting::menu(){
 std::cout<<"Bienvenido a mi programa de subneto!!";
 bool menu = true;
 int option = 0;
 while(menu){
    std::cout<<"Menú de opciónes:\n";
    std::cout<<"Ingrese 1 si desea realizar el subnetting de uno de los archivos disponibles\n";
    std::cout<<"Ingrese 2 si desea salir del programa\n";
    std::cin>>option;
    switch(option){
        case 1:
        this->subnetting_menu();
        break;
        case 2:
        std::cout<<"Hasta luego!, Recuerda que puedes consultar los resultados\n";
        menu = false;
        break;
    }
 }
}

void Subnetting::clear_vectors(std::vector<int>& sols, std::vector<char>& ranges, std::vector<int>& masks){
    sols.clear();
    ranges.clear();
    masks.clear();
}

void Subnetting::subnetting_menu(){
    int option = 0;
    std::cout<<"Opciones de archivos para resolver\n";
    for(int i = 0; i<6; i++){
        std::cout<<"Archivo: " <<this->files[i] <<"\n";
    }

    std::cout<<"Ingrese el número de cual archivo desea resolver\n";
    std::cin>>option;
    this->set_values_from_file(this->files[option]);
    std::cout<<"Ingresa 1 si desea asignar los rangos de las direcciones de mayor a menor\n";
    std::cout<<"Ingresa 2 si desea asignar los rangos de las direcciones de menor a mayor\n";
    std::cin>>option;
    if(option == 1){
    this->send_prove(true);
    this->make_calc();
    }else{
     this->send_prove(false);
     this->make_calc();
    }
    std::cout<<"Cálculo realizado con éxito, recuerda revisar el archivo prueba con los resultados\n";
}


 void Subnetting::get_ip_ready_lower_upper(int sols_total){
    int sol_size = sols_total;
     bool first_entry = true;
        if(!first_entry){
          this->work_ip[3]++;
          if(this->work_ip[3] == 256){
            this->work_ip[3] = 0;
            this->work_ip[2]++;
            if(this->work_ip[2] == 256){
                this->work_ip[2] = 0;
                this->work_ip[1]++;
                if(this->work_ip[1] == 256){
                    this->work_ip[1] = 0;
                    this->work_ip[0]++;
                }
            }
          }
        }
        
        bool option = true;
        this->work_ip[3]++;
        if(this->work_ip[3] == 256){
            this->work_ip[3] = 0;
            this->work_ip[2]++;
            if(this->work_ip[2] == 256){
                this->work_ip[2] = 0;
                this->work_ip[1]++;
                if(this->work_ip[1] == 256){
                    this->work_ip[1] = 0;
                    this->work_ip[0]++;
                }
            }
          }
        sol_size--;
        while(option){
            if(sol_size + this->work_ip[3] > 256){
                int discount_value = 255 - this->work_ip[3];
                sol_size = sol_size - discount_value;
                this->work_ip[2]++;
                if(this->work_ip[2] > 255){
                    this->work_ip[2] = 0;
                    this->work_ip[1]++;
                    if(this->work_ip[1] > 255){
                        this->work_ip[1] = 0;
                        this->work_ip[0]++;
                    }
                }
                this->work_ip[3] = 0;               
            }else if(sol_size + this->work_ip[3] < 256){
                this->work_ip[3]+= sol_size;
                option = false;
                first_entry = false;
            }else if(sol_size + this->work_ip[3] == 256){
                this->work_ip[3]+= sol_size-1;
                this->work_ip[3] = 0;
                this->work_ip[2]++;
                if(this->work_ip[2] > 255){
                    this->work_ip[2] = 0;
                    this->work_ip[1]++;
                    if(this->work_ip[1] > 255){
                        this->work_ip[1] = 0;
                        this->work_ip[0]++;
                    }
                }
                option = false;    
                first_entry = true;
            }
            sol_size--;
        }
    }
    
void Subnetting::send_prove(bool option){
 //ojito para las pruebas
 int sols_size = 0;
 if(option){
 this->sort_ranges_upper(this->sols,this->ranges);
 }else{
    int pivot = 0;
    int pivot_ammount = 0;
    sols_size = this->calc_sol_total_size();
    std::cout<<sols_size <<"\n";
    pivot_ammount = this->get_needed_sols(sols_size,pivot);
    pivot_ammount = pivot_ammount - sols_size; 
    std::cout<<"Prueba: " << pivot_ammount <<"\n";
    this->get_ip_ready_lower_upper(pivot_ammount);
    this->sort_ranges_lower(this->sols,this->ranges);
    }
 for(int i = 0; i<this->ranges_count; i++){
    int power = 0;
    int mask = 0;
    int sols_ = this->get_needed_sols(this->sols[i],power);
    this->sols[i] = sols_;
    mask = this->get_mask(power);
    this->masks.push_back(mask);
 }
 //this->make_calc();
}



void Subnetting::make_calc(){
    bool first_entry = true;
    // Copiamos 
    for(int i = 0; i<this->ranges_count; i++){
        std::string net_id = "";
        std::string frist_available_direction = "";
        std::string last_available_direction = "";
        std::string broadcast_direction = "";
        std::string concant = "";
        int sol_size = this->sols[i];
        int actual_maks = this->masks[i];
        if(!first_entry){
          this->work_ip[3]++;
          if(this->work_ip[3] == 256){
            this->work_ip[3] = 0;
            this->work_ip[2]++;
            if(this->work_ip[2] == 256){
                this->work_ip[2] = 0;
                this->work_ip[1]++;
                if(this->work_ip[1] == 256){
                    this->work_ip[1] = 0;
                    this->work_ip[0]++;
                    if(this->work_ip[0] == 256){
                      std::cout<<"No hay espacio disponible para esta solicitud\n";
                      std::ofstream file("Results.txt", std::ios::trunc);
                      return;
                    }
                }
            }
          }
        }
        
        for(int i = 0; i<4; i++){
            net_id+= std::to_string(this->work_ip[i]);
            if(i!=3){
            net_id+= '.';
            }
         }
         concant = "";
        bool option = true;
        this->work_ip[3]++;
        if(this->work_ip[3] == 256){
            this->work_ip[3] = 0;
            this->work_ip[2]++;
            if(this->work_ip[2] == 256){
                this->work_ip[2] = 0;
                this->work_ip[1]++;
                if(this->work_ip[1] == 256){
                    this->work_ip[1] = 0;
                    this->work_ip[0]++;
                    if(this->work_ip[0] == 256){
                      std::cout<<"No hay espacio disponible para esta solicitud\n";
                      std::ofstream file("Results.txt", std::ios::trunc);
                      return;
                    }
                }
            }
          }
        concant = std::to_string(this->work_ip[3]);
        for(int i = 0; i<3; i++){
            frist_available_direction+= std::to_string(this->work_ip[i]);
            frist_available_direction+= '.';
        }
        frist_available_direction+= concant;
        concant = "";
        sol_size--;
        while(option){
           // std::cout<<"Estado de la solicitud " <<sol_size + this->work_ip[3] <<"\n";
            if(sol_size + this->work_ip[3] > 256){
                int discount_value = 255 - this->work_ip[3];
                sol_size = sol_size - discount_value;
                this->work_ip[2]++;
                if(this->work_ip[2] > 255){
                    this->work_ip[2] = 0;
                    this->work_ip[1]++;
                    if(this->work_ip[1] > 255){
                        this->work_ip[1] = 0;
                        this->work_ip[0]++;
                        if(this->work_ip[0] == 256){
                      std::cout<<"No hay espacio disponible para esta solicitud\n";
                      std::ofstream file("Results.txt", std::ios::trunc);
                      return;
                    }
                    }
                }
                this->work_ip[3] = 0;               
            }else if(sol_size + this->work_ip[3] < 256){
                for(int i = 0; i<3; i++){
                  last_available_direction += std::to_string(this->work_ip[i]);
                  last_available_direction+= '.';
                  broadcast_direction += std::to_string(this->work_ip[i]);
                  broadcast_direction+= '.';
                }
                last_available_direction += std::to_string(this->work_ip[3] + (sol_size -2));
                this->work_ip[3]+= sol_size -1;
                broadcast_direction += std::to_string(this->work_ip[3]);
                option = false;
                first_entry = false;
            }else if(sol_size + this->work_ip[3] == 256){
                  for(int i = 0; i<3; i++){
                  last_available_direction += std::to_string(this->work_ip[i]);
                  last_available_direction+= '.';
                  broadcast_direction += std::to_string(this->work_ip[i]);
                  broadcast_direction+= '.';
                }
                last_available_direction += std::to_string(this->work_ip[3] + (sol_size -2));
                this->work_ip[3]+= sol_size-1;
                broadcast_direction += std::to_string(this->work_ip[3]);
                this->work_ip[3] = 0;
                this->work_ip[2]++;
                if(this->work_ip[2] > 255){
                    this->work_ip[2] = 0;
                    this->work_ip[1]++;
                    if(this->work_ip[1] > 255){
                        this->work_ip[1] = 0;
                        this->work_ip[0]++;
                        if(this->work_ip[0] > 256){
                         std::cout<<"No hay espacio disponible para esta solicitud\n";
                         std::ofstream file("Results.txt", std::ios::trunc);
                      return;
                    }
                    }
                }
                option = false;    
                first_entry = true;
            }
            sol_size--;
        }
     this->safe_data_on_file(ranges[i],actual_maks,net_id,frist_available_direction,last_available_direction,broadcast_direction);
    }
}

int Subnetting::calc_sol_total_size(){
    int total = 0;
    int pivot = 0;
    int result = 0;
    for(size_t i = 0; i<this->sols.size(); i++){
        result = this->get_needed_sols(sols[i],pivot);
        total+= result;
    }
    return total;
}

int Subnetting::get_needed_sols(int sols, int& power){
    if(sols == 1){
        power = 2;
       return 4;
    }
    int requiered_sols = sols + 2;
    int power_of_two = 0;
    for(int i = 0; i<32; i++){
        power_of_two = std::pow(2,i);
        if(requiered_sols <= power_of_two){
            power = i;
            return power_of_two;
        }
    }
    return 0;
}

void Subnetting::sort_ranges_lower(std::vector<int>& sols_ , std::vector<char>& ranges_){
     for(size_t i = 0; i<sols_.size(); i++){
        int min = sols_[i];
        int index = i;
        char range = ranges_[i];
        for(size_t j = i +1; j<sols_.size(); j++){
            if(sols_[j] < min){
                min = sols_[j];
                index = j;
                range = ranges_[j];
            }
        }
        int pivot = sols_[i];
        char pivot_c = ranges_[i];
        sols_[i] = min;
        ranges_[i] = range;
        sols_[index] = pivot;
        ranges_[index] = pivot_c; 
    }
}

int Subnetting::get_mask(int power){
    return 32 - power;
}


void Subnetting::sort_ranges_upper(std::vector<int>& sols_ , std::vector<char>& ranges_){
    for(size_t i = 0; i<sols_.size(); i++){
        int max = sols_[i];
        int index = i;
        char range = ranges_[i];
        for(size_t j = i +1; j<sols_.size(); j++){
            if(sols_[j] > max){
                max = sols_[j];
                index = j;
                range = ranges_[j];
            }
        }
        int pivot = sols_[i];
        char pivot_c = ranges_[i];
        sols_[i] = max;
        ranges_[i] = range;
        sols_[index] = pivot;
        ranges_[index] = pivot_c; 

    }
}

void Subnetting::prove(){
    //this->sort_ranges(this->sols,this->ranges);
}

void Subnetting::safe_data_on_file(const char range,const int mask, const std::string net_id,std::string first_available, std::string last_available, std::string broadcast){
    std::ofstream file("Results.txt", std::ios::app);
    
    if(!file.is_open()){
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }
    file << "Rango: " << range << "\n";
    file << "Máscara: " << mask << "\n";
    file << "Net ID: " << net_id << "\n";
    file << "Primera dirección disponible: " << first_available << "\n";
    file << "Última dirección disponible: " << last_available << "\n";
    file << "Dirección de Broadcast: " << broadcast << "\n";
    file << "----------------------------------------\n";

    this->clear_vectors(this->sols,this->ranges,this->masks);

    file.close();
}

int main(){
    Subnetting s;
    s.menu();
    //s.print_values_prove();
    //std::cout<<"Inicio de pruebas\n";
   // s.send_prove();
    return 0;
}