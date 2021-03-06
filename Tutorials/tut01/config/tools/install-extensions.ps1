$vscode_path = Get-Command code
If ([string]::IsNullOrEmpty($vscode_path)) {
   'Visual Studio Code not found. Please download and install Visual Studio Code from https://code.visualstudio.com/download.'
   exit 1
}

code --install-extension eamodio.gitlens                             -and \
code --install-extension Equinusocio.vsc-community-material-theme    -and \
code --install-extension Equinusocio.vsc-material-theme              -and \
code --install-extension equinusocio.vsc-material-theme-icons        -and \
code --install-extension GitHub.vscode-pull-request-github           -and \
code --install-extension helgardrichard.helium-icon-theme            -and \
code --install-extension j-zeppenfeld.tab-indent-space-align         -and \
code --install-extension llvm-vs-code-extensions.vscode-clangd       -and \
code --install-extension ms-vscode-remote.remote-wsl                 -and \
code --install-extension ms-vscode.cmake-tools                       -and \
code --install-extension twxs.cmake                                  -and \
code --install-extension vadimcn.vscode-lldb                         -and \
code --install-extension webfreak.debug
