// texture_storage.cc

#include "graphics/texture_storage.hpp"
#include "platform/filestream.hpp"
#include "platform/filesystem.hpp"
#include "platform/debug.hpp"

#include <cassert>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// font: 
// - Fira Mono
// - Liberation Mono

namespace papaya {
   namespace {
      constexpr Texture::Format texture_format(const int components)
      {
         switch (components)
         {
            case 3: return Texture::Format::Rgb8;
            case 4: return Texture::Format::Rgba8;
         }

         assert(!"Unknown component count!");
         return Texture::Format::Rgba8;
      }
   } // !anon

   TextureStorage::TextureStorage(FileSystem &filesystem)
      : filesystem_(filesystem)
   {
   }

   TextureStorage::~TextureStorage()
   {
      for (auto &it : storage_) {
         it.second.destroy();
      }
   }

   bool TextureStorage::is_loaded(const char *filename) const
   {
      const auto it = storage_.find(filename);
      return it != storage_.end();
   }

   void TextureStorage::load(const char *filename)
   {
      if (is_loaded(filename)) {
         return;
      }

      FileStream stream = filesystem_.open(filename);
      if (!stream.is_valid()) {
         Debug::log("Could not open file: '%s'", filename);
         return;
      }

      std::vector<char> file_content;
      int64 size = stream.size();
      file_content.resize(size);
      if (size != stream.read(file_content.size(), file_content.data())) {
         assert(!"Error reading file content!");
      }
      stream.close();

      int width = 0;
      int height = 0;
      int components = 0;
      stbi_uc *data = stbi_load_from_memory((const stbi_uc *)file_content.data(),
                                            (int)file_content.size(),
                                            &width,
                                            &height,
                                            &components,
                                            STBI_default);
      if (data == nullptr) {
         assert(false && "Error could not parse image data!");
      }

      auto f = texture_format(components);

      Texture texture;
      bool success = texture.create(f, width, height, data);
      stbi_image_free(data);

      if (!success) {
         Debug::log("Could not create texture! '%s'", filename);
         return;
      }

      storage_.emplace(filename, texture);
      Debug::log("Loaded texture: '%s'", filename);
   }

   void TextureStorage::unload(const char *filename)
   {
      const auto it = storage_.find(filename);
      if (it == storage_.end()) {
         Debug::log("Could not unload the texture: '%s'", filename);
         return;
      }

      it->second.destroy();
      storage_.erase(it);

      Debug::log("Unloaded texture: '%s'", filename);
   }

   const Texture *TextureStorage::find(const char *filename) const
   {
      const auto it = storage_.find(filename);
      if (it != storage_.end()) {
         return &it->second;
      }

      return nullptr;
   }
} // !papaya
