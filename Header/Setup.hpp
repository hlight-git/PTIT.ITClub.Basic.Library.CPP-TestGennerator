#ifndef SETUP_HPP
#define SETUP_HPP

        #include "ITPlib.hpp"

            void Set_Info(Problem_Info& in4){
                in4.number_of_test_case = 15;
                in4.limit_size_of_file = 500000; //bytes
            }
            void Easy(ofstream& fout){
                /*  Modify here  */fout << 1;
            }
            void Medium(ofstream& fout){
                /*  Modify here  */fout << 1;
            }
            void Hard(ofstream& fout){
                /*  Modify here  */fout << 1;
            }
        // Nếu muốn thêm mức cực khó, bỏ cmt hàm sau và chỉnh sửa:
            // #define NIGHTMARE
            //     int quantity = 3; // Số lượng test cực khó.
            //     void NightMare(ofstream& fout){
            //         /*  Modify here  */
            //     }
            
#endif