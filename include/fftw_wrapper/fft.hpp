/**
|============================================ fft.hpp =============================================|
|                                                                                                  |
|   Property of Daniel Sturdivant. Unauthorized copying of this file via any medium is would be    |
|   super sad and unfortunate for me. Proprietary and confidential.                                |
|                                                                                                  |
|--------------------------------------------------------------------------------------------------|
|                                                                                                  |
|   @file     include/sdr/core/algorithm/fft.hpp                                                   |
|   @brief    Fast fourier transform utilities.                                                    |
|   @author   Daniel Sturdivant <sturdivant20@gmail.com>                                           |
|   @date     April 2024                                                                           |
|                                                                                                  |
|==================================================================================================|
*/

#ifndef FFTW_WRAPPER_HPP
#define FFTW_WRAPPER_HPP

#include <fftw3.h>
#include <spdlog/spdlog.h>

#include <complex>
#include <vector>

namespace fftw_wrapper {

class FftwWrapper {
  public:
    //* === FftwWrapper ===
    /// @brief constructor
    FftwWrapper();

    //* === ~FftwWrapper ===
    /// @brief destructor
    ~FftwWrapper();

    //* === create_fft_plan ===
    /// @brief create fft plan
    /// @param in input stream to take fft of
    /// @param out fft result
    /// @param len length of fft to take
    /// @return True|False based on creation of plan
    bool create_fft_plan(std::complex<double>* in, std::complex<double>* out, int len);
    bool create_fft_plan(std::vector<std::complex<double>>& in,
                         std::vector<std::complex<double>>& out, int len);

    //* === create_ifft_plan ===
    /// @brief create ifft plan
    /// @param in input stream to take fft of
    /// @param out fft result
    /// @param len length of fft to take
    /// @return True|False based on creation of plan
    bool create_ifft_plan(std::complex<double>* in, std::complex<double>* out, int len);
    bool create_ifft_plan(std::vector<std::complex<double>>& in,
                          std::vector<std::complex<double>>& out, int len);

    //* === fft ===
    /// @brief run fft
    /// @param in input stream to take fft of
    /// @param out fft result
    /// @param len length of fft to take
    /// @return True|False based on FFT success
    bool fft();

    //* === fft ===
    /// @brief run inverse fft
    /// @param in input stream to take inverse fft of
    /// @param out ifft result
    /// @param len length of fft to take
    /// @return True|False based on IFFT success
    bool ifft();

  private:
    /// @brief fftw plan variables
    fftw_plan _fft, _ifft;
    std::shared_ptr<spdlog::logger> _log;

};  // end class fft
}  // namespace fftw_wrapper

#endif