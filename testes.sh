#!/bin/bash

# Função para verificar se a porta está em uso
check_port() {
    ss -tuln | grep -q ":$1 "
    return $?
}

# Verifica a porta 8080; se estiver em uso, utiliza a porta 3000
if check_port 8080; then
    SERVER_URL="http://localhost:8080"
else
    SERVER_URL="http://localhost:3000"
fi

# Arquivos para testar
FILES=("index.html" "hinoBotafogo.txt" "loccoAbreu.jpeg" "erroHTML.html" "erroTEXTO.txt" "erroIMG.jpeg")

# Número de requisições
NUM_REQUESTS=50

make_request() {
    local file=$1
    curl -s -o /dev/null -w "%{http_code} %{url_effective}\n" "$SERVER_URL/$file"
}

for FILE in "${FILES[@]}"
do
    for ((i=1; i<=NUM_REQUESTS; i++))
    do
        make_request "$FILE" &
    done
done

wait

echo "Test completed with $NUM_REQUESTS requests for each file."

#chmod +x testes.sh
#./testes.sh