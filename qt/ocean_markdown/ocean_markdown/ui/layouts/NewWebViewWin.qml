import QtQuick
import QtWebEngine

Window{

    property alias _webview: _webview
    WebEngineView{
        id: _webview
    }
}
