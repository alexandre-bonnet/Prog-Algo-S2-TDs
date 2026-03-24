#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <stack>

enum class Operator { ADD, SUB, MUL, DIV};
enum class TokenType { OPERATOR, OPERAND };
struct Token {
  TokenType type;
  float value;
  Operator op;
};

Token make_token(float value){
    return Token{TokenType::OPERAND, value};
}

Token make_token(Operator op){
    return Token{TokenType::OPERATOR, 0, op};
}

bool is_floating(std::string const& s){
    for (char c : s) {
        if((!std::isdigit(c))&&(c!='.')){
            return false;
        }
    } 
    return true;
}

std::vector<Token> tokenize(std::vector<std::string> const& words){
    int vectorSize = words.size();
    std::vector<Token> tokens(vectorSize);
    for(int i = 0; i<vectorSize; i++){
        std::string word = words[i];
        Token token{};
        if(is_floating(word)){
            token = make_token(std::stof(word));
        } else {
            if(word=="+"){
                token = make_token(Operator::ADD);
            } else if(word=="-"){
                token = make_token(Operator::SUB);
            } else if(word=="*"){
                token = make_token(Operator::MUL);
            } else if(word=="/"){
                token = make_token(Operator::DIV);
            }
        }
        tokens[i] = token;
    }
    return tokens;
}

std::vector<std::string> split_string(std::string const& s){
    std::istringstream in(s); // transforme une chaîne en flux de caractères, cela simule un flux comme l'est std::cin
    // l’itérateur va lire chaque element de "in", comme un flux d'entrée, chaque élément est séparé par un espace
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()); 
}

float npi_evaluate(std::vector<Token> const& tokens){
    std::stack<float> stack;
    for(Token token : tokens){
        if(token.type==TokenType::OPERAND){
            stack.push(token.value);
        } else {
            // Je récupère l'élément en haut de la pile
            float rightOperand { stack.top() };
            // Je l'enlève de la stack (la méthode top ne fait que lire l’élément en dessus de la pile)
            stack.pop();
            float leftOperand { stack.top() };
            stack.pop();
            // Il faut ensuite en fonction de l'opérateur calculer le résultat pour le remettre dans la pile
            float result{};
            if(token.op==Operator::ADD){
                result = leftOperand+rightOperand;
            } else if(token.op==Operator::SUB){
                result = leftOperand-rightOperand;
            } else if(token.op==Operator::MUL){
                result = leftOperand*rightOperand;
            } else if(token.op==Operator::DIV){
                result = leftOperand/rightOperand;
            }
            stack.push(result);
        }
    } return stack.top();
}

int main(){
    std::string expression;

    std::cout << "Entrez une expression en notation polonaise inversee : ";
    std::getline(std::cin, expression);

    std::cout << "Expression saisie : '" << expression <<"'"<< std::endl;
    std::vector<Token> tokens = tokenize(split_string(expression));
    std::cout << "Le resultat est : "<< npi_evaluate(tokens) << std::endl;
}