class Message{
    private:
        int choice;
        double value;
        char dt[32];

    public:
        Message(){
            choice = 0;
            value = 0;
        }
        
        void setChoice(int w){
            choice = w;
        }

        void setValue(double v){
            value = v;
        }

        void setDT(char* d){
            strncpy(dt,d,32);
        }

        int getChoice() const{
            return choice;
        }

        double getValues() const{
            return value;
        }

        std::string getDT() const{
            return dt;
        }
};