
```
ollama serve
ollama run codellama:13b-instruct-q4_K_M

$env:STRIX_LLM="ollama/codellama:13b-instruct-q4_K_M"
$env:LLM_API_BASE="http://localhost:11434"
strix --target .
```
