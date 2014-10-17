#include "debugger.h"

#include "Event/event.h"

Debugger::Debugger():
    EventListener()
{
    dw.add_log("Debugger...");
}

void Debugger::eventRecieved(Event e){
    if(e.type == Event::EventDebuggerMessage){
        dw.add_log(e.debugger->getDebugMessage());
        //qDebug(e.debugger->getDebugMessage().toUtf8());
        return;
    }
    if(e.type == Event::EventDebuggerShow){
        dw.show();
        return;
    }
    if(e.type == Event::EventDebuggerHide){
        dw.hide();
        return;
    }
    if(e.type == Event::EventDebuggerFPS){
        dw.add_fps_data(e.debugger->getDebugValue());
        return;
    }
    if(e.type == Event::EventDebuggerNSPerFrame){
        dw.add_ns_data(e.debugger->getDebugValue());
        return;
    }
    if(e.type == Event::EventDebuggerMeshsPerFrame){
        dw.add_mpf_data(e.debugger->getDebugValue());
        return;
    }
    if(e.type == Event::EventDebuggerTrianglesPerFrame){
        dw.add_tpf_data(e.debugger->getDebugValue());
        return;
    }
    if(e.type == Event::EventDebuggerTimeStep){
        dw.add_ts_data(e.debugger->getDebugValue());
        return;
    }
    if(e.type == Event::EventDebuggerTexBindsPerFrame){
        dw.add_tb_data(e.debugger->getDebugValue());
        return;
    }
}
