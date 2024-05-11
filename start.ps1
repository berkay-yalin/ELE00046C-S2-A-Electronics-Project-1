function script:GetDeviceData() {
    $detect = [System.Collections.ArrayList]@(mbed-tools detect)
    $detect.RemoveAt(1)
    $detect = foreach ($row in $detect) {
        $h = $row -split "\s{2,}"
        , $h
    }

    $data = @{}
    for ($i = 0; $i -lt $detect[0].Count; $i++) {
        $data[$detect[0][$i]] = $detect[1][$i]
    }
    return $data
}

function script:GetSourceTarget([string]$mountPoint, [string]$buildTarget) {
    $binaryName = (Get-Location).Path.split("\")[-1] + ".bin"

    $source = Join-Path (Get-Location).Path "cmake_build" $buildTarget "develop" "GCC_ARM" $binaryName
    $target = Join-Path $mountPoint $binaryName
    return $source, $target
}

$deviceData = GetDeviceData

mbed-tools compile -m $deviceData["Build target(s)"] -t GCC_ARM

$source, $target = GetSourceTarget $deviceData["Mount Point(s)"] $deviceData["Build target(s)"]

Copy-Item $source $target

