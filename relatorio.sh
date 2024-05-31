#!/bin/bash

./web_server -p 8080 -l log.txt -s stats.txt -r ./  &
PROGRAM_PID=$!

# Esperar alguns segundos para o programa iniciar
sleep 2

# Monitorar processos e threads
ps -eLf | grep web_server > process_threads_report.txt

# Monitorar uso de memória
echo "Memory usage:" > memory_report.txt
pmap $PROGRAM_PID >> memory_report.txt


# Interromper o programa após um tempo definido (exemplo: 10 segundos)
sleep 40
kill -SIGINT $PROGRAM_PID

# Aguardar o AddressSanitizer gerar o relatório
wait $PROGRAM_PID

echo "Reports generated:"
echo "  - AddressSanitizer report on terminal"
echo "  - process_threads_report.txt"
echo "  - memory_report.txt"
