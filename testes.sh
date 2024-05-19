#!/bin/bash

# URL do servidor
SERVER_URL="http://localhost:8080"

# Arquivos para testar
FILES=("index.html" "file.txt" "image.jpg")

# Número de requisições
NUM_REQUESTS=100

for ((i=1; i<=NUM_REQUESTS; i++))
do
    for FILE in "${FILES[@]}"
    do
        curl -s -o /dev/null -w "%{http_code} %{url_effective}\n" "$SERVER_URL/$FILE" &
    done
done

# Espera todos os processos terminarem
wait

echo "Test completed with $NUM_REQUESTS requests for each file."

#chmod +x testes.sh
#./testes.sh