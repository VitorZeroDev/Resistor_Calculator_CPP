🔌 Calculadora de Resistores (4 e 5 Faixas) em C

Este projeto calcula o valor de resistores com 4 ou 5 faixas baseado nas cores padrões do código internacional. Também permite calcular resistência equivalente (série/paralelo) e exportar resultados para um arquivo .txt, tudo direto no terminal e com visualização colorida no Windows.

📊 Objetivo

- Interpretar faixas de cores de resistores (4 e 5 bandas).
- Calcular automaticamente o valor nominal do resistor.
- Formatar resultados em Ohms, kΩ ou MΩ.
- Calcular resistência equivalente (série ou paralelo).
- Exibir tabela colorida no terminal.
- Exportar cálculos para arquivo .txt.

🛠️ Tecnologias utilizadas

- C (ANSI/Windows)
- windows.h — cor no console
- math.h — potências
- stdio.h / stdlib.h — entrada, saída e arquivos
- string.h — validações e strings

⚙️ Funcionalidades

✔️ Tabela de cores com visualização real  
✔️ Cálculo de resistores 4 / 5 faixas  
✔️ Conversão automática de unidades  
✔️ Verificação completa das entradas  
✔️ Resistência equivalente em série/paralelo  
✔️ Exportação para .txt  
✔️ Interface simples via terminal  

🧩 Como compilar o projeto

```bash
gcc src/calculadora_resistores.c -o calculadora
```

Após compilar, será criado:

```bash
calculadora.exe
```

▶️ Como executar

```bash
./calculadora
```

📁 Estrutura do projeto

/docs
    overview.md
/models
/src
    calculadora_resistores.c
/tests
    README-tests.md
LICENSE
README.md


📌 Licença
Este projeto está sob a licença MIT.
