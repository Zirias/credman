#ifndef UTILS_JSONSER_H
#define UTILS_JSONSER_H

typedef enum JsonFormatting
{
    JsonFormatting_Compact,
    JsonFormatting_Indented
} JsonFormatting;

typedef struct JsonOptions
{
    JsonFormatting formatting;
} JsonOptions;

typedef struct JsonSerializer JsonSerializer;

JsonSerializer * JsonSerializer_Create(JsonOptions options);

#endif
