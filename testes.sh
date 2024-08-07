#!/bin/bash

SERVER_URL="http://localhost:8080/testes"


FILES=("index.html"  "index_imagem.html" "index_texto.html" "index_texto_imagem.html")

NUM_REQUESTS=5

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
