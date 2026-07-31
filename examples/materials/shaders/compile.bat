@echo off
set GLSLC=C:\VulkanSDK\1.4.309.0\Bin\glslc.exe

echo ==========================================
echo [1/3] Compilation of shader RELEASE versions
echo ==========================================
%GLSLC% vert.vert -o vert.spv
%GLSLC% frag.frag -o frag.spv

echo ==========================================
echo [2/3] Compilation of basic DEBUG versions
echo ==========================================
%GLSLC% vert_debug.vert -o vert_debug.spv
%GLSLC% frag_debug.frag -o frag_debug.spv

echo ==========================================
echo [3/3] Generation of specialized DEBUG views
echo ==========================================
:: Визуализация нормалей (синий/фиолетовый оттенок)
%GLSLC% frag_debug.frag -o frag_debug_normals.spv -DDEBUG_NORMALS

:: Визуализация UV-развертки (градиент от черного к желтому)
%GLSLC% frag_debug.frag -o frag_debug_uv.spv -DDEBUG_UV

:: Визуализация карт PBR-материалов (Metallic/Roughness/AO)
%GLSLC% frag_debug.frag -o frag_debug_mrao.spv -DDEBUG_MRAO

:: Визуализация только прямого света (черные тени без Ambient)
%GLSLC% frag_debug.frag -o frag_debug_lighting.spv -DDEBUG_LIGHTING

:: Визуализация смещения текстурных координат от POM
%GLSLC% frag_debug.frag -o frag_debug_pom.spv -DDEBUG_POM

echo ==========================================
echo The compilation is completed successfully!
echo ==========================================
pause