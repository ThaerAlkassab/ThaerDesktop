"use strict";

document.addEventListener("DOMContentLoaded", function () {
    // Navbar behavior on scroll
    window.addEventListener("scroll", function () {
        if (window.pageYOffset > 5) {
            document.querySelector(".navbar").classList.add("active");
        } else {
            document.querySelector(".navbar").classList.remove("active");
        }
    });

    // ScrollSpy initialization
    var scrollSpy = new bootstrap.ScrollSpy(document.body, {
        target: "#navbar",
        offset: 50,
    });
});

function showTranscript(image) {
    const transcriptWindow = window.open("", "_blank");
    transcriptWindow.document.write('<img src="' + image + '" alt="Transcript" style="width:100%;">');
}

function showCertificate(image) {
    const certificateWindow = window.open("", "_blank");
    certificateWindow.document.write('<img src="' + image + '" alt="Certificate" style="width:100%;">');
}
