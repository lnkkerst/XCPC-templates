// This file was generated by [ts-rs](https://github.com/Aleph-Alpha/ts-rs). Do not edit this file manually.
import type { BookItem } from "./BookItem";

/**
 * A dumb tree structure representing a book.
 *
 * For the moment a book is just a collection of [`BookItems`] which are
 * accessible by either iterating (immutably) over the book with [`iter()`], or
 * recursively applying a closure to each section to mutate the chapters, using
 * [`for_each_mut()`].
 *
 * [`iter()`]: #method.iter
 * [`for_each_mut()`]: #method.for_each_mut
 */
export type Book = {
  /**
   * The sections in this book.
   */
  sections: Array<BookItem>;
  __non_exhaustive: null;
};
