"use strict";

// Navbar Behavior
document.addEventListener("DOMContentLoaded", function () {
    window.addEventListener("scroll", function () {
        if (window.pageYOffset > 5) {
            document.querySelector(".navbar").classList.add("active");
        } else {
            document.querySelector(".navbar").classList.remove("active");
        }
    });

    // Bootstrap ScrollSpy
    var scrollSpy = new bootstrap.ScrollSpy(document.body, {
        target: "#navbar",
        offset: 50,
    });

    // Function to download the CV as a PDF
    document.getElementById("downloadCV").addEventListener("click", function () {
        window.location.href = "CV.pdf"; // Update with actual path to CV.pdf
    });

    // Function to show/hide the transcript section
    document.getElementById("showTranscript").addEventListener("click", function () {
        const transcript = document.getElementById("transcript");
        transcript.style.display = transcript.style.display === "none" ? "block" : "none";
    });

    // Function to show/hide the certificates section
    document.getElementById("showCertificates").addEventListener("click", function () {
        const certificates = document.getElementById("certificates");
        certificates.style.display = certificates.style.display === "none" ? "block" : "none";
    });
});
