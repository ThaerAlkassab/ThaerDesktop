// Function to format time with leading zero if needed
function formatTime(time) {
    return time < 10 ? "0" + time : time;
}

function addAppointment() {
    // JavaScript function to add appointments to the calendar
    var daySelect = document.getElementById("day-select");
    var selectedDay = daySelect.value;
    console.log("Selected Day:", selectedDay);
    
    var hourSelect = document.getElementById("appointment-hour");
    var hour = hourSelect.value;
    console.log("Selected Hour:", hour);
    
    var minuteSelect = document.getElementById("appointment-minute");
    var minute = minuteSelect.value;
    console.log("Selected Minute:", minute);
    
    var lengthInput = document.getElementById("appointment-length");
    var length = parseInt(lengthInput.value);
    console.log("Length of Appointment:", length);
    
    var textInput = document.getElementById("appointment-text");
    var text = textInput.value;
    console.log("Appointment Description:", text);

    // Example validation function for time
    function isValidTime(hour, minute) {
        if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
            return true;
        } else {
            return false;
        }
    }

    if (hour && minute && !isNaN(length) && length > 0 && text && selectedDay !== "") {
        if (isValidTime(hour, minute)) {
            var startHour = parseInt(hour);
            var startMinute = parseInt(minute);
            var endHour = startHour + Math.floor((startMinute + length) / 60);
            var endMinute = (startMinute + length) % 60;

            console.log("Start Hour:", startHour);
            console.log("Start Minute:", startMinute);
            console.log("End Hour:", endHour);
            console.log("End Minute:", endMinute);

            var startCell = document.getElementById("row-" + startHour + "-" + selectedDay);
            var endCell = document.getElementById("row-" + endHour + "-" + selectedDay);

            console.log("Start Cell:", startCell);
            console.log("End Cell:", endCell);

            if (startCell && endCell) {
                var appointment = document.createElement("div");
                appointment.className = "appointment";
                appointment.textContent = text + " (" + formatTime(hour) + ":" + formatTime(minute) + " - " + formatTime(endHour) + ":" + formatTime(endMinute) + ")";

                // Calculate the height of the appointment
                var height = (endHour - startHour) * 60 + (endMinute - startMinute); // in minutes
                appointment.style.height = height * 2 + "px"; // assuming each hour is 2px height

                // Calculate the position within the table
                var position = startCell.getBoundingClientRect().top + (startCell.offsetHeight / 60) * startMinute;
                appointment.style.top = position - startCell.parentNode.getBoundingClientRect().top + "px"; // Adjusting for table offset

                // Adjusting width to fit within cell
                var cellWidth = startCell.offsetWidth;
                appointment.style.width = cellWidth - 10 + "px"; // Adjusting for padding and border

                startCell.appendChild(appointment);
            }
        }
    }

    hourSelect.value = "";
    minuteSelect.value = "";
    lengthInput.value = "";
    textInput.value = "";
}
