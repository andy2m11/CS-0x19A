


	
/*******************************************************************************
static void
dump_headers (bfd *abfd)
{
  printf (_("Sections:\n"));

#ifndef BFD64
  printf (_("Idx Name          Size      VMA       LMA       File off  Algn"));
#else
  // With BFD64, non-ELF returns -1 and wants always 64 bit addresses.  
  if (bfd_get_arch_size (abfd) == 32)
    printf (_("Idx Name          Size      VMA       LMA       File off  Algn"));
  else
    printf (_("Idx Name          Size      VMA               LMA               File off  Algn"));
#endif

  if (wide_output)
    printf (_("  Flags"));
  if (abfd->flags & HAS_LOAD_PAGE)
    printf (_("  Pg"));
  printf ("\n");

  bfd_map_over_sections (abfd, dump_section_header, NULL);
}

********************************************************************************/
static void bfd_init(void);
static void bfd_openr();
static void bfd_check_format();
static void bfd_perror();
static void bfd_map_over_sections();
static void bfd_get_symtab_upper_bound();
static void bfd_canonicalize_symtab();
static void typedef struct _bfd bfd;
static void typedef struct sec asection;
static void typedef struct symbol_cache_entry asymbol;

/******
void bfd_section_list_clear (bfd *);
asection *bfd_get_section_by_name (bfd *abfd, const char *name);
asection *bfd_get_next_section_by_name (asection *sec);
asection *bfd_get_linker_section (bfd *abfd, const char *name);
asection *bfd_get_section_by_name_if
        (bfd *abfd,
         const char *name,
         bfd_boolean (*func) (bfd *abfd, asection *sect, void *obj),
         void *obj);
func (abfd, the_section, obj);    
char *bfd_get_unique_section_name(bfd *abfd, const char *templat, int *count);     
asection *bfd_make_section_old_way (bfd *abfd, const char *name);     
asection *bfd_make_section_anyway_with_flags
        (bfd *abfd, const char *name, flagword flags);    
asection *bfd_make_section_anyway (bfd *abfd, const char *name);    
asection *bfd_make_section_with_flags
        (bfd *, const char *name, flagword flags);
asection *bfd_make_section (bfd *, const char *name);        
bfd_boolean bfd_set_section_flags
        (bfd *abfd, asection *sec, flagword flags);        
void bfd_rename_section
        (bfd *abfd, asection *sec, const char *newname);        
void bfd_map_over_sections
        (bfd *abfd,
         void (*func) (bfd *abfd, asection *sect, void *obj),
         void *obj);        
        
        
        
        
        
        
        
        
        
        
        
********/





     typedef struct bfd_section
     {
       /* The name of the section; the name isn't a copy, the pointer is
          the same as that passed to bfd_make_section.  */
       const char *name;
     
       /* A unique sequence number.  */
       int id;
     
       /* Which section in the bfd; 0..n-1 as sections are created in a bfd.  */
       int index;
     
       /* The next section in the list belonging to the BFD, or NULL.  */
       struct bfd_section *next;
     
       /* The previous section in the list belonging to the BFD, or NULL.  */
       struct bfd_section *prev;
     
       /* The field flags contains attributes of the section. Some
          flags are read in from the object file, and some are
          synthesized from other information.  */
       flagword flags;
     
     #define SEC_NO_FLAGS   0x000
     
       /* Tells the OS to allocate space for this section when loading.
          This is clear for a section containing debug information only.  */
     #define SEC_ALLOC      0x001
     
       /* Tells the OS to load the section from the file when loading.
          This is clear for a .bss section.  */
     #define SEC_LOAD       0x002
     
       /* The section contains data still to be relocated, so there is
          some relocation information too.  */
     #define SEC_RELOC      0x004
     
       /* A signal to the OS that the section contains read only data.  */
     #define SEC_READONLY   0x008
     
       /* The section contains code only.  */
     #define SEC_CODE       0x010
     
       /* The section contains data only.  */
     #define SEC_DATA       0x020
     
       /* The section will reside in ROM.  */
     #define SEC_ROM        0x040
     
       /* The section contains constructor information. This section
          type is used by the linker to create lists of constructors and
          destructors used by g++. When a back end sees a symbol
          which should be used in a constructor list, it creates a new
          section for the type of name (e.g., __CTOR_LIST__), attaches
          the symbol to it, and builds a relocation. To build the lists
          of constructors, all the linker has to do is catenate all the
          sections called __CTOR_LIST__ and relocate the data
          contained within - exactly the operations it would peform on
          standard data.  */
     #define SEC_CONSTRUCTOR 0x080
     
       /* The section has contents - a data section could be
          SEC_ALLOC | SEC_HAS_CONTENTS; a debug section could be
          SEC_HAS_CONTENTS  */
     #define SEC_HAS_CONTENTS 0x100
     
       /* An instruction to the linker to not output the section
          even if it has information which would normally be written.  */
     #define SEC_NEVER_LOAD 0x200
     
       /* The section contains thread local data.  */
     #define SEC_THREAD_LOCAL 0x400
     
       /* The section has GOT references.  This flag is only for the
          linker, and is currently only used by the elf32-hppa back end.
          It will be set if global offset table references were detected
          in this section, which indicate to the linker that the section
          contains PIC code, and must be handled specially when doing a
          static link.  */
     #define SEC_HAS_GOT_REF 0x800
     
       /* The section contains common symbols (symbols may be defined
          multiple times, the value of a symbol is the amount of
          space it requires, and the largest symbol value is the one
          used).  Most targets have exactly one of these (which we
          translate to bfd_com_section_ptr), but ECOFF has two.  */
     #define SEC_IS_COMMON 0x1000
     
       /* The section contains only debugging information.  For
          example, this is set for ELF .debug and .stab sections.
          strip tests this flag to see if a section can be
          discarded.  */
     #define SEC_DEBUGGING 0x2000
     
       /* The contents of this section are held in memory pointed to
          by the contents field.  This is checked by bfd_get_section_contents,
          and the data is retrieved from memory if appropriate.  */
     #define SEC_IN_MEMORY 0x4000
     
       /* The contents of this section are to be excluded by the
          linker for executable and shared objects unless those
          objects are to be further relocated.  */
     #define SEC_EXCLUDE 0x8000
     
       /* The contents of this section are to be sorted based on the sum of
          the symbol and addend values specified by the associated relocation
          entries.  Entries without associated relocation entries will be
          appended to the end of the section in an unspecified order.  */
     #define SEC_SORT_ENTRIES 0x10000
     
       /* When linking, duplicate sections of the same name should be
          discarded, rather than being combined into a single section as
          is usually done.  This is similar to how common symbols are
          handled.  See SEC_LINK_DUPLICATES below.  */
     #define SEC_LINK_ONCE 0x20000
     
       /* If SEC_LINK_ONCE is set, this bitfield describes how the linker
          should handle duplicate sections.  */
     #define SEC_LINK_DUPLICATES 0xc0000
     
       /* This value for SEC_LINK_DUPLICATES means that duplicate
          sections with the same name should simply be discarded.  */
     #define SEC_LINK_DUPLICATES_DISCARD 0x0
     
       /* This value for SEC_LINK_DUPLICATES means that the linker
          should warn if there are any duplicate sections, although
          it should still only link one copy.  */
     #define SEC_LINK_DUPLICATES_ONE_ONLY 0x40000
     
       /* This value for SEC_LINK_DUPLICATES means that the linker
          should warn if any duplicate sections are a different size.  */
     #define SEC_LINK_DUPLICATES_SAME_SIZE 0x80000
     
       /* This value for SEC_LINK_DUPLICATES means that the linker
          should warn if any duplicate sections contain different
          contents.  */
     #define SEC_LINK_DUPLICATES_SAME_CONTENTS \
       (SEC_LINK_DUPLICATES_ONE_ONLY | SEC_LINK_DUPLICATES_SAME_SIZE)
     
       /* This section was created by the linker as part of dynamic
          relocation or other arcane processing.  It is skipped when
          going through the first-pass output, trusting that someone
          else up the line will take care of it later.  */
     #define SEC_LINKER_CREATED 0x100000
     
       /* This section should not be subject to garbage collection.
          Also set to inform the linker that this section should not be
          listed in the link map as discarded.  */
     #define SEC_KEEP 0x200000
     
       /* This section contains "short" data, and should be placed
          "near" the GP.  */
     #define SEC_SMALL_DATA 0x400000
     
       /* Attempt to merge identical entities in the section.
          Entity size is given in the entsize field.  */
     #define SEC_MERGE 0x800000
     
       /* If given with SEC_MERGE, entities to merge are zero terminated
          strings where entsize specifies character size instead of fixed
          size entries.  */
     #define SEC_STRINGS 0x1000000
     
       /* This section contains data about section groups.  */
     #define SEC_GROUP 0x2000000
     
       /* The section is a COFF shared library section.  This flag is
          only for the linker.  If this type of section appears in
          the input file, the linker must copy it to the output file
          without changing the vma or size.  FIXME: Although this
          was originally intended to be general, it really is COFF
          specific (and the flag was renamed to indicate this).  It
          might be cleaner to have some more general mechanism to
          allow the back end to control what the linker does with
          sections.  */
     #define SEC_COFF_SHARED_LIBRARY 0x4000000
     
       /* This input section should be copied to output in reverse order
          as an array of pointers.  This is for ELF linker internal use
          only.  */
     #define SEC_ELF_REVERSE_COPY 0x4000000
     
       /* This section contains data which may be shared with other
          executables or shared objects. This is for COFF only.  */
     #define SEC_COFF_SHARED 0x8000000
     
       /* When a section with this flag is being linked, then if the size of
          the input section is less than a page, it should not cross a page
          boundary.  If the size of the input section is one page or more,
          it should be aligned on a page boundary.  This is for TI
          TMS320C54X only.  */
     #define SEC_TIC54X_BLOCK 0x10000000
     
       /* Conditionally link this section; do not link if there are no
          references found to any symbol in the section.  This is for TI
          TMS320C54X only.  */
     #define SEC_TIC54X_CLINK 0x20000000
     
       /* Indicate that section has the no read flag set. This happens
          when memory read flag isn't set. */
     #define SEC_COFF_NOREAD 0x40000000
     
       /*  End of section flags.  */
     
       /* Some internal packed boolean fields.  */
     
       /* See the vma field.  */
       unsigned int user_set_vma : 1;
     
       /* A mark flag used by some of the linker backends.  */
       unsigned int linker_mark : 1;
     
       /* Another mark flag used by some of the linker backends.  Set for
          output sections that have an input section.  */
       unsigned int linker_has_input : 1;
     
       /* Mark flag used by some linker backends for garbage collection.  */
       unsigned int gc_mark : 1;
     
       /* Section compression status.  */
       unsigned int compress_status : 2;
     #define COMPRESS_SECTION_NONE    0
     #define COMPRESS_SECTION_DONE    1
     #define DECOMPRESS_SECTION_SIZED 2
     
       /* The following flags are used by the ELF linker. */
     
       /* Mark sections which have been allocated to segments.  */
       unsigned int segment_mark : 1;
     
       /* Type of sec_info information.  */
       unsigned int sec_info_type:3;
     #define SEC_INFO_TYPE_NONE      0
     #define SEC_INFO_TYPE_STABS     1
     #define SEC_INFO_TYPE_MERGE     2
     #define SEC_INFO_TYPE_EH_FRAME  3
     #define SEC_INFO_TYPE_JUST_SYMS 4
     
       /* Nonzero if this section uses RELA relocations, rather than REL.  */
       unsigned int use_rela_p:1;
     
       /* Bits used by various backends.  The generic code doesn't touch
          these fields.  */
     
       unsigned int sec_flg0:1;
       unsigned int sec_flg1:1;
       unsigned int sec_flg2:1;
       unsigned int sec_flg3:1;
       unsigned int sec_flg4:1;
       unsigned int sec_flg5:1;
     
       /* End of internal packed boolean fields.  */
     
       /*  The virtual memory address of the section - where it will be
           at run time.  The symbols are relocated against this.  The
           user_set_vma flag is maintained by bfd; if it's not set, the
           backend can assign addresses (for example, in a.out, where
           the default address for .data is dependent on the specific
           target and various flags).  */
       bfd_vma vma;
     
       /*  The load address of the section - where it would be in a
           rom image; really only used for writing section header
           information.  */
       bfd_vma lma;
     
       /* The size of the section in octets, as it will be output.
          Contains a value even if the section has no contents (e.g., the
          size of .bss).  */
       bfd_size_type size;
     
       /* For input sections, the original size on disk of the section, in
          octets.  This field should be set for any section whose size is
          changed by linker relaxation.  It is required for sections where
          the linker relaxation scheme doesn't cache altered section and
          reloc contents (stabs, eh_frame, SEC_MERGE, some coff relaxing
          targets), and thus the original size needs to be kept to read the
          section multiple times.  For output sections, rawsize holds the
          section size calculated on a previous linker relaxation pass.  */
       bfd_size_type rawsize;
     
       /* The compressed size of the section in octets.  */
       bfd_size_type compressed_size;
     
       /* Relaxation table. */
       struct relax_table *relax;
     
       /* Count of used relaxation table entries. */
       int relax_count;
     
     
       /* If this section is going to be output, then this value is the
          offset in *bytes* into the output section of the first byte in the
          input section (byte ==> smallest addressable unit on the
          target).  In most cases, if this was going to start at the
          100th octet (8-bit quantity) in the output section, this value
          would be 100.  However, if the target byte size is 16 bits
          (bfd_octets_per_byte is "2"), this value would be 50.  */
       bfd_vma output_offset;
     
       /* The output section through which to map on output.  */
       struct bfd_section *output_section;
     
       /* The alignment requirement of the section, as an exponent of 2 -
          e.g., 3 aligns to 2^3 (or 8).  */
       unsigned int alignment_power;
     
       /* If an input section, a pointer to a vector of relocation
          records for the data in this section.  */
       struct reloc_cache_entry *relocation;
     
       /* If an output section, a pointer to a vector of pointers to
          relocation records for the data in this section.  */
       struct reloc_cache_entry **orelocation;
     
       /* The number of relocation records in one of the above.  */
       unsigned reloc_count;
     
       /* Information below is back end specific - and not always used
          or updated.  */
     
       /* File position of section data.  */
       file_ptr filepos;
     
       /* File position of relocation info.  */
       file_ptr rel_filepos;
     
       /* File position of line data.  */
       file_ptr line_filepos;
     
       /* Pointer to data for applications.  */
       void *userdata;
     
       /* If the SEC_IN_MEMORY flag is set, this points to the actual
          contents.  */
       unsigned char *contents;
     
       /* Attached line number information.  */
       alent *lineno;
     
       /* Number of line number records.  */
       unsigned int lineno_count;
     
       /* Entity size for merging purposes.  */
       unsigned int entsize;
     
       /* Points to the kept section if this section is a link-once section,
          and is discarded.  */
       struct bfd_section *kept_section;
     
       /* When a section is being output, this value changes as more
          linenumbers are written out.  */
       file_ptr moving_line_filepos;
     
       /* What the section number is in the target world.  */
       int target_index;
     
       void *used_by_bfd;
     
       /* If this is a constructor section then here is a list of the
          relocations created to relocate items within it.  */
       struct relent_chain *constructor_chain;
     
       /* The BFD which owns the section.  */
       bfd *owner;
     
       /* A symbol which points at this section only.  */
       struct bfd_symbol *symbol;
       struct bfd_symbol **symbol_ptr_ptr;
     
       /* Early in the link process, map_head and map_tail are used to build
          a list of input sections attached to an output section.  Later,
          output sections use these fields for a list of bfd_link_order
          structs.  */
       union {
         struct bfd_link_order *link_order;
         struct bfd_section *s;
       } map_head, map_tail;
     } asection;
     
     /* Relax table contains information about instructions which can
        be removed by relaxation -- replacing a long address with a
        short address.  */
     struct relax_table {
       /* Address where bytes may be deleted. */
       bfd_vma addr;
     
       /* Number of bytes to be deleted.  */
       int size;
     };
     
     /* These sections are global, and are managed by BFD.  The application
        and target back end are not permitted to change the values in
        these sections.  */
     extern asection _bfd_std_section[4];
     
     #define BFD_ABS_SECTION_NAME "*ABS*"
     #define BFD_UND_SECTION_NAME "*UND*"
     #define BFD_COM_SECTION_NAME "*COM*"
     #define BFD_IND_SECTION_NAME "*IND*"
     
     /* Pointer to the common section.  */
     #define bfd_com_section_ptr (&_bfd_std_section[0])
     /* Pointer to the undefined section.  */
     #define bfd_und_section_ptr (&_bfd_std_section[1])
     /* Pointer to the absolute section.  */
     #define bfd_abs_section_ptr (&_bfd_std_section[2])
     /* Pointer to the indirect section.  */
     #define bfd_ind_section_ptr (&_bfd_std_section[3])
     
     #define bfd_is_und_section(sec) ((sec) == bfd_und_section_ptr)
     #define bfd_is_abs_section(sec) ((sec) == bfd_abs_section_ptr)
     #define bfd_is_ind_section(sec) ((sec) == bfd_ind_section_ptr)
     
     #define bfd_is_const_section(SEC)              \
      (   ((SEC) == bfd_abs_section_ptr)            \
       || ((SEC) == bfd_und_section_ptr)            \
       || ((SEC) == bfd_com_section_ptr)            \
       || ((SEC) == bfd_ind_section_ptr))
     
     /* Macros to handle insertion and deletion of a bfd's sections.  These
        only handle the list pointers, ie. do not adjust section_count,
        target_index etc.  */
     #define bfd_section_list_remove(ABFD, S) \
       do                                                   \
         {                                                  \
           asection *_s = S;                                \
           asection *_next = _s->next;                      \
           asection *_prev = _s->prev;                      \
           if (_prev)                                       \
             _prev->next = _next;                           \
           else                                             \
             (ABFD)->sections = _next;                      \
           if (_next)                                       \
             _next->prev = _prev;                           \
           else                                             \
             (ABFD)->section_last = _prev;                  \
         }                                                  \
       while (0)
     #define bfd_section_list_append(ABFD, S) \
       do                                                   \
         {                                                  \
           asection *_s = S;                                \
           bfd *_abfd = ABFD;                               \
           _s->next = NULL;                                 \
           if (_abfd->section_last)                         \
             {                                              \
               _s->prev = _abfd->section_last;              \
               _abfd->section_last->next = _s;              \
             }                                              \
           else                                             \
             {                                              \
               _s->prev = NULL;                             \
               _abfd->sections = _s;                        \
             }                                              \
           _abfd->section_last = _s;                        \
         }                                                  \
       while (0)
     #define bfd_section_list_prepend(ABFD, S) \
       do                                                   \
         {                                                  \
           asection *_s = S;                                \
           bfd *_abfd = ABFD;                               \
           _s->prev = NULL;                                 \
           if (_abfd->sections)                             \
             {                                              \
               _s->next = _abfd->sections;                  \
               _abfd->sections->prev = _s;                  \
             }                                              \
           else                                             \
             {                                              \
               _s->next = NULL;                             \
               _abfd->section_last = _s;                    \
             }                                              \
           _abfd->sections = _s;                            \
         }                                                  \
       while (0)
     #define bfd_section_list_insert_after(ABFD, A, S) \
       do                                                   \
         {                                                  \
           asection *_a = A;                                \
           asection *_s = S;                                \
           asection *_next = _a->next;                      \
           _s->next = _next;                                \
           _s->prev = _a;                                   \
           _a->next = _s;                                   \
           if (_next)                                       \
             _next->prev = _s;                              \
           else                                             \
             (ABFD)->section_last = _s;                     \
         }                                                  \
       while (0)
     #define bfd_section_list_insert_before(ABFD, B, S) \
       do                                                   \
         {                                                  \
           asection *_b = B;                                \
           asection *_s = S;                                \
           asection *_prev = _b->prev;                      \
           _s->prev = _prev;                                \
           _s->next = _b;                                   \
           _b->prev = _s;                                   \
           if (_prev)                                       \
             _prev->next = _s;                              \
           else                                             \
             (ABFD)->sections = _s;                         \
         }                                                  \
       while (0)
     #define bfd_section_removed_from_list(ABFD, S) \
       ((S)->next == NULL ? (ABFD)->section_last != (S) : (S)->next->prev != (S))
     
     #define BFD_FAKE_SECTION(SEC, FLAGS, SYM, NAME, IDX)                   \
       /* name, id,  index, next, prev, flags, user_set_vma,            */  \
       { NAME,  IDX, 0,     NULL, NULL, FLAGS, 0,                           \
                                                                            \
       /* linker_mark, linker_has_input, gc_mark, decompress_status,    */  \
          0,           0,                1,       0,                        \
                                                                            \
       /* segment_mark, sec_info_type, use_rela_p,                      */  \
          0,            0,             0,                                   \
                                                                            \
       /* sec_flg0, sec_flg1, sec_flg2, sec_flg3, sec_flg4, sec_flg5,   */  \
          0,        0,        0,        0,        0,        0,              \
                                                                            \
       /* vma, lma, size, rawsize, compressed_size, relax, relax_count, */  \
          0,   0,   0,    0,       0,               0,     0,               \
                                                                            \
       /* output_offset, output_section, alignment_power,               */  \
          0,             &SEC,           0,                                 \
                                                                            \
       /* relocation, orelocation, reloc_count, filepos, rel_filepos,   */  \
          NULL,       NULL,        0,           0,       0,                 \
                                                                            \
       /* line_filepos, userdata, contents, lineno, lineno_count,       */  \
          0,            NULL,     NULL,     NULL,   0,                      \
                                                                            \
       /* entsize, kept_section, moving_line_filepos,                    */ \
          0,       NULL,          0,                                        \
                                                                            \
       /* target_index, used_by_bfd, constructor_chain, owner,          */  \
          0,            NULL,        NULL,              NULL,               \
                                                                            \
       /* symbol,                    symbol_ptr_ptr,                    */  \
          (struct bfd_symbol *) SYM, &SEC.symbol,                           \
                                                                            \
       /* map_head, map_tail                                            */  \
          { NULL }, { NULL }                                                \
         }
     



