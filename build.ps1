if(!$env:BUILD_ENV) {
  $env:SOC_ROOT=$PSScriptRoot;
  $env:KAUAI_ROOT="$env:SOC_ROOT\kauai";
  $env:include="$env:include;$env:SOC_ROOT\INC;$env:SOC_ROOT\BREN\INC;$env:KAUAI_ROOT\SRC;$env:SOC_ROOT\SRC";
  $env:BLD_TYPE_DIR='WINUS';
  $env:ARCH='WIN';
  $env:CHAR='UNICODE';
  $env:PROJ='SOC';
  $env:TYPE='DBSHIP';
  $env:BUILD_ENV=$true;
}
cl /nologo /c "$env:SOC_ROOT\stub.cpp" "/Fo$env:SOC_ROOT\stub.obj" `
&& lib /nologo "$env:SOC_ROOT\stub.obj" "/OUT:$env:SOC_ROOT\stub.lib" `
&& Push-Location .\kauai `
&& nmake /nologo;

Pop-Location;

if($LASTEXITCODE) {
  Write-Error 'Build failed (kauai)'
  return;
}

nmake /nologo;
if($LASTEXITCODE) {
  Write-Error 'Build failed'
  return;
}