$(function() {
    const ipcRenderer = require('electron').ipcRenderer;
    const HFProcess = require('./modules/hf-process.js');

    function onProcessUpdate(event, arg) {
        console.log("update", event, arg);

        // var interfaceState = arg.interface.state;
        // $('#process-interface .status').text(interfaceState);
        // var interfaceOn = interfaceState != 'stopped';
        // $('#process-interface .power-on').prop('disabled', interfaceOn);
        // $('#process-interface .power-off').prop('disabled', !interfaceOn);

        var sendingProcess = arg;

        var processCircle = null;
        if (sendingProcess.name == "domain-server") {
            processCircle = $('#ds-status .circle');
        } else if (sendingProcess.name == "ac-monitor") {
            processCircle = $('#ac-status .circle');
        } else {
            return;
        }

        switch (sendingProcess.state) {
            case HFProcess.ProcessStates.STOPPED:
                processCircle.attr('class', 'circle stopped');
                break;
            case HFProcess.ProcessStates.STOPPING:
                processCircle.attr('class', 'circle stopping');
                break;
            case HFProcess.ProcessStates.STARTED:
                processCircle.attr('class', 'circle started');
                break;
        }
    }

    function onProcessGroupUpdate(event, arg) {
        var sendingGroup = arg;
        var stopButton = $('#manage-server #stop');

        switch (sendingGroup.state) {
            case HFProcess.ProcessGroupStates.STOPPED:
                // if the process group is stopped, the stop button should be disabled
                stopButton.removeAttr('href');
                break;
            case HFProcess.ProcessGroupStates.STOPPING:
                break;
            case HFProcess.ProcessGroupStates.STARTED:
                console.log("SETTING HREF");
                // if the process group is going, the stop button should be active
                stopButton.attr('href', '#');
                break;
        }
    }

    $('#process-interface .power-on').click(function() {
        ipcRenderer.send('start-process', { name: 'interface' });
    });
    $('#process-interface .power-off').click(function() {
        ipcRenderer.send('stop-process', { name: 'interface' });
    });
    $('#manage-server #restart').click(function() {
        ipcRenderer.send('restart-server', { name: 'home' });
    });
    $('#manage-server #stop').click(function() {
        ipcRenderer.send('stop-server', { name: 'home' });
    });
    $('#open-logs').click(function() {
        ipcRenderer.send('open-logs');
    });

    ipcRenderer.on('process-update', onProcessUpdate);
    ipcRenderer.on('process-group-update', onProcessGroupUpdate);

    ipcRenderer.send('update-all-processes');
});
