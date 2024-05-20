/**
|============================================ fft.cpp =============================================|
|                                                                                                  |
|   Property of Daniel Sturdivant. Unauthorized copying of this file via any medium is would be    |
|   super sad and unfortunate for me. Proprietary and confidential.                                |
|                                                                                                  |
|--------------------------------------------------------------------------------------------------|
|                                                                                                  |
|   @file     src/algorithm/fft.hpp                                                                |
|   @brief    Fast fourier transform utilities.                                                    |
|   @author   Daniel Sturdivant <sturdivant20@gmail.com>                                           |
|   @date     April 2024                                                                           |
|                                                                                                  |
|==================================================================================================|
*/

#include "fftw_wrapper/fft.hpp"

#include <exception>

namespace fftw_wrapper {

// ----------------------------------- Constructor/Destructor ----------------------------------- //

//* === FftwWrapper ===
FftwWrapper::FftwWrapper() : _log(spdlog::default_logger()) {
    fftw_make_planner_thread_safe();
}

//* === ~FftwWrapper ===
FftwWrapper::~FftwWrapper() {
    fftw_destroy_plan(_fft);
    fftw_destroy_plan(_ifft);
}

// ------------------------------------------- Public ------------------------------------------- //

//* === creat_fft_plan ===
bool FftwWrapper::create_fft_plan(std::complex<double>* in, std::complex<double>* out, int len) {
    try {
        // execute ifft
        _fft = fftw_plan_dft_1d(len, reinterpret_cast<fftw_complex*>(in),
                                reinterpret_cast<fftw_complex*>(out), FFTW_FORWARD, FFTW_ESTIMATE);
        return true;

    } catch (std::exception const& e) {
        _log->warn("FftwWrapper::create_fft_plan failed. ERROR {}", e.what());
        return false;
    }
}

//* === creat_fft_plan ===
bool FftwWrapper::create_fft_plan(std::vector<std::complex<double>>& in,
                                  std::vector<std::complex<double>>& out, int len) {
    try {
        // execute ifft
        _fft = fftw_plan_dft_1d(len, reinterpret_cast<fftw_complex*>(in.data()),
                                reinterpret_cast<fftw_complex*>(out.data()), FFTW_FORWARD,
                                FFTW_ESTIMATE);
        return true;

    } catch (std::exception const& e) {
        _log->warn("FftwWrapper::create_fft_plan failed. ERROR {}", e.what());
        return false;
    }
}

//* === creat_ifft_plan ===
bool FftwWrapper::create_ifft_plan(std::complex<double>* in, std::complex<double>* out, int len) {
    try {
        // execute ifft
        _ifft =
            fftw_plan_dft_1d(len, reinterpret_cast<fftw_complex*>(in),
                             reinterpret_cast<fftw_complex*>(out), FFTW_BACKWARD, FFTW_ESTIMATE);
        return true;

    } catch (std::exception const& e) {
        _log->warn("FftwWrapper::create_ifft_plan failed. ERROR {}", e.what());
        return false;
    }
}

//* === creat_ifft_plan ===
bool FftwWrapper::create_ifft_plan(std::vector<std::complex<double>>& in,
                                   std::vector<std::complex<double>>& out, int len) {
    try {
        // execute ifft
        _ifft = fftw_plan_dft_1d(len, reinterpret_cast<fftw_complex*>(in.data()),
                                 reinterpret_cast<fftw_complex*>(out.data()), FFTW_BACKWARD,
                                 FFTW_ESTIMATE);
        return true;

    } catch (std::exception const& e) {
        _log->warn("FftwWrapper::create_ifft_plan failed. ERROR {}", e.what());
        return false;
    }
}

//* === fft ===
bool FftwWrapper::fft() {
    try {
        // execute fft
        fftw_execute(_fft);
        return true;

    } catch (std::exception const& e) {
        _log->warn("FftwWrapper::fft failed. ERROR {}", e.what());
        return false;
    }
}

//* === ifft ===
bool FftwWrapper::ifft() {
    try {
        // execute ifft
        fftw_execute(_ifft);
        return true;

    } catch (std::exception const& e) {
        _log->warn("FftwWrapper::ifft failed. ERROR {}", e.what());
        return false;
    }
}

// ------------------------------------------- Private ------------------------------------------ //

}  // namespace fftw_wrapper