#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'
NC='\033[0m' # Sin color

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <host> <port>"
    exit 1
fi

resultado=$(echo -e "GET / HTTP/1.1\r\nHost: $1\r\n\r\n" | nc "$1" "$2" 2>/dev/null)
LONGITUD_MAXIMA=200

if echo "$resultado" | grep -q "Connection refused"; then
    echo "Puerto $2: connectio refused"
elif [ -z "$resultado" ]; then
    :  # void
else
    if [ "${#resultado}" -gt "$LONGITUD_MAXIMA" ]; then
        if [ "$2" -eq 80 ]; then
            version=$(echo "$resultado" | grep -i 'Version:')
            apache=$(echo "$resultado" | grep -i 'Apache')
            if [ -n "$version" ]; then
                echo -e "${RED}>> TCP ${YELLOW}\\ open \\ ${RED}$2 ${GREEN}$version"
            elif [ -n "$apache" ]; then
                echo -e "${RED}>> TCP ${YELLOW}\\ open \\ ${RED}$2 ${GREEN}$apache"
            else
                echo -e "${RED}>> TCP ${YELLOW}\\ open \\ ${RED}$2 ${GREEN}(versions not found)"
            fi
        else
            echo -e "${RED}>> TCP ${YELLOW}\\ open \\ ${RED}$2 ${GREEN}(version no encontrada)"
        fi
    else
        if [ "$2" -eq 80 ]; then
            version=$(echo "$resultado" | grep -i 'Version:')
            apache=$(echo "$resultado" | grep -i 'Apache')
            if [ -n "$version" ]; then
                echo -e "${RED}>> TCP ${YELLOW}\\ open \\ ${RED}$2 ${GREEN}$version"
            elif [ -n "$apache" ]; then
                echo -e "${RED}>> TCP ${YELLOW}\\ open \\ ${RED}$2 ${GREEN}$apache"
            else
                echo -e "${RED}>> TCP ${YELLOW}\\ open \\ ${RED}$2 ${GREEN}$resultado"
            fi
        else
            servidor=$(echo "$resultado" | grep -i 'Server:' | tr -d '\r')
            if [ -n "$servidor" ]; then
                echo -e "${RED}>> TCP ${YELLOW}\\ open \\ ${RED}$2 ${GREEN}$servidor"
            else
                echo -e "${RED}>> TCP ${YELLOW}\\ open \\ ${RED}$2 ${GREEN}$resultado"
            fi
        fi
    fi
fi
